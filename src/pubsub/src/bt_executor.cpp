#include "bt_executor.h"

#include "publisher_node.cpp"
#include "subscriber_node.cpp"

using namespace std;
using namespace std::chrono;
using namespace rclcpp;
using namespace BT;

BTExecutor::BTExecutor(const string &node_name) : Node(node_name) {
  this->declare_parameter("bt", PARAMETER_STRING);
  this->declare_parameter("tick_rate_ms", PARAMETER_INTEGER);
  RCLCPP_INFO(get_logger(), "Started BT Executor");
}

void BTExecutor::setup() {
  RCLCPP_INFO(get_logger(), "Started BT Setup");
  createBehaviorTree();
  RCLCPP_INFO(get_logger(), "Created BT Successfully");
  Parameter intParam = this->get_parameter("tick_rate_ms");
  int tickRateMs = intParam.as_int();
  duration timerPeriod = duration<int, ratio<1, 1000>>(tickRateMs);
  timer_ = this->create_wall_timer(timerPeriod,
                                   bind(&BTExecutor::updateBehaviorTree, this));
  spin(shared_from_this());
}

void BTExecutor::haltBehaviorTree() {
  timer_->cancel();
  shutdown();
}

void BTExecutor::updateBehaviorTree() {
  NodeStatus treeStatus = tree_.tickRoot();
  if (treeStatus == NodeStatus::FAILURE) {
    RCLCPP_INFO(get_logger(), "BT Ended with FAILURE");
    haltBehaviorTree();
  } else if (treeStatus == NodeStatus::SUCCESS) {
    RCLCPP_INFO(get_logger(), "BT Ended with SUCCESS");
    haltBehaviorTree();
  }
}

void BTExecutor::createBehaviorTree() {
  Parameter strParam = this->get_parameter("bt");
  string treeXml = strParam.as_string();

  RCLCPP_INFO(get_logger(), "Registering Nodes");
  NodeBuilder builder = [=](const string &name,
                            const NodeConfiguration &config) {
    return std::make_unique<PublisherNode>(name, config, shared_from_this());
  };
  factory_.registerBuilder<PublisherNode>("Publisher", builder);
  builder = [=](const string &name, const NodeConfiguration &config) {
    return std::make_unique<SubscriberNode>(name, config, shared_from_this());
  };
  factory_.registerBuilder<SubscriberNode>("Subscriber", builder);

  RCLCPP_INFO(get_logger(), "Creating Tree %s", treeXml.c_str());
  tree_ = factory_.createTreeFromFile(treeXml);
}

int main(int argc, char **argv) {
  init(argc, argv);
  shared_ptr node = make_shared<BTExecutor>("bt_executor");
  node->setup();
  return 0;
}
