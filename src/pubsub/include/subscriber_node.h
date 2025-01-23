#ifndef SUBSCRIBER_NODE_H
#define SUBSCRIBER_NODE_H

#include <behaviortree_cpp_v3/condition_node.h>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <string>

class SubscriberNode : public BT::ConditionNode {
 public:
  explicit SubscriberNode(const std::string&, const BT::NodeConfiguration&,
                          rclcpp::Node::SharedPtr);
  BT::NodeStatus tick() override;
  static BT::PortsList providedPorts();
  void updateMsg(const std_msgs::msg::String::SharedPtr);
  bool waitForMessage(int);

 private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr strSubscriberPtr_;
  std::string msg_;
};

#endif  // SUBSCRIBER_NODE_H
