#include <behaviortree_cpp_v3/bt_factory.h>

#include <chrono>
#include <fstream>
#include <rclcpp/rclcpp.hpp>
#include <string>

#include "PublisherBT.h"
#include "SubscriberBT.h"

using namespace std;
using namespace std::chrono;
using namespace BT;
using namespace rclcpp;

class BTExecutor : public Node {
 public:
  BTExecutor(const string &nodeName) : Node(nodeName) {
    this->declare_parameter("bt", PARAMETER_STRING);
    this->declare_parameter("tick_rate_ms", PARAMETER_INTEGER);
    RCLCPP_INFO(get_logger(), "Started BT Executor");
  }

  void setup() {
    RCLCPP_INFO(get_logger(), "Started BT Setup");
    createBehaviorTree();
    RCLCPP_INFO(get_logger(), "Created BT Successfully");
    Parameter int_param = this->get_parameter("tick_rate_ms");
    int tickRateMs = int_param.as_int();
    duration timerPeriod = duration<int, ratio<1, 1000>>(tickRateMs);
    timer_ = this->create_wall_timer(
        timerPeriod, bind(&BTExecutor::updateBehaviorTree, this));
    spin(shared_from_this());
  }

  void createBehaviorTree() {
    Parameter strParam = this->get_parameter("bt");
    string treeXml = strParam.as_string();
    RCLCPP_INFO(get_logger(), "Registering Nodes");
    NodeBuilder builder = [=](const string &name,
                              const NodeConfiguration &config) {
      return std::make_unique<PublisherBT>(name, config, shared_from_this());
    };
    factory_.registerBuilder<PublisherBT>("Publisher", builder);
    builder = [=](const string &name, const NodeConfiguration &config) {
      return std::make_unique<SubscriberBT>(name, config, shared_from_this());
    };
    factory_.registerBuilder<SubscriberBT>("Subscriber", builder);
    RCLCPP_INFO(get_logger(), "Creating Tree %s", treeXml.c_str());
    tree_ = factory_.createTreeFromFile(treeXml);
  }

  void updateBehaviorTree() {
    NodeStatus treeStatus = tree_.tickRoot();
    if (treeStatus == NodeStatus::FAILURE) {
      RCLCPP_INFO(get_logger(), "BT Ended with FAILURE");
      haltBehaviorTree();
    } else if (treeStatus == NodeStatus::SUCCESS) {
      RCLCPP_INFO(get_logger(), "BT Ended with SUCCESS");
      haltBehaviorTree();
    }
  }

  void haltBehaviorTree() {
    timer_->cancel();
    shutdown();
  }

 private:
  BehaviorTreeFactory factory_;

  TimerBase::SharedPtr timer_;

  Tree tree_;
};

int main(int argc, char **argv) {
  init(argc, argv);
  shared_ptr node = make_shared<BTExecutor>("bt_executor");
  node->setup();
  return 0;
}
