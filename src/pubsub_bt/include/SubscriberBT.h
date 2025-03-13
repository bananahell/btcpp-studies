#ifndef SUBSCRIBERBT_H
#define SUBSCRIBERBT_H

#include <behaviortree_cpp_v3/condition_node.h>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class SubscriberBT : public BT::ConditionNode {
 public:
  SubscriberBT(const std::string&, const BT::NodeConfiguration&,
               rclcpp::Node::SharedPtr);

  BT::NodeStatus tick();

  static BT::PortsList providedPorts();

  void updateMsg(const std_msgs::msg::String::SharedPtr);

  bool waitForMessage(int);

 private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr strSubscriberPtr_;

  std::string msg_;
};

#endif  // SUBSCRIBERBT_H
