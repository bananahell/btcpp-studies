#ifndef BT_EXECUTOR_H
#define BT_EXECUTOR_H

#include <behaviortree_cpp_v3/bt_factory.h>

#include <rclcpp/rclcpp.hpp>
#include <string>

class BTExecutor : public rclcpp::Node {
 public:
  explicit BTExecutor(const std::string &);
  void setup();
  void createBehaviorTree();
  void updateBehaviorTree();
  void haltBehaviorTree();

 private:
  BT::BehaviorTreeFactory factory_;
  rclcpp::TimerBase::SharedPtr timer_;
  BT::Tree tree_;
};

#endif  // BT_EXECUTOR_H
