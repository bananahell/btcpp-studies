#ifndef PUBLISHERBT_H
#define PUBLISHERBT_H

#include <behaviortree_cpp_v3/action_node.h>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class PublisherBT : public BT::SyncActionNode {
 public:
  PublisherBT(const std::string&, const BT::NodeConfiguration&,
              rclcpp::Node::SharedPtr);

  BT::NodeStatus tick();

  static BT::PortsList providedPorts();

 private:
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr strPublisherPtr_;
};

#endif  // PUBLISHERBT_H
