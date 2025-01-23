#ifndef PUBLISHER_NODE_H
#define PUBLISHER_NODE_H

#include <behaviortree_cpp_v3/action_node.h>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <string>

class PublisherNode : public BT::SyncActionNode {
 public:
  explicit PublisherNode(const std::string &, const BT::NodeConfiguration &,
                         rclcpp::Node::SharedPtr);
  BT::NodeStatus tick() override;
  static BT::PortsList providedPorts();

 private:
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr strPublisherPtr_;
};

#endif  // PUBLISHER_NODE_H
