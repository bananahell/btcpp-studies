#include <nav2_behavior_tree/bt_action_node.hpp>

#include "custom_action_interfaces/action/fibonacci.hpp"

using namespace BT;
using Fibonacci = custom_action_interfaces::action::Fibonacci;
using GoalHandleFibonacci = rclcpp_action::ServerGoalHandle<Fibonacci>;

class FibonacciAction : nav2_behavior_tree::BtActionNode<Fibonacci> {
 public:
  FibonacciAction(const std::string& xml_tag_name,
                  const std::string& action_name, const NodeConfiguration& conf)
      : BtActionNode(xml_tag_name, action_name, conf) {}

  static PortsList providedPorts() {
    return providedBasicPorts({InputPort<unsigned>("order")});
  }
};

/*

class FibonacciAction : public nav2_behavior_tree::BtActionNode<Fibonacci> {
 public:
  FibonacciAction(const std::string& name, const NodeConfig& conf,
                  const RosNodeParams& params)
      : BtActionNode<Fibonacci>(name, conf, params) {}

  // The specific ports of this Derived class
  // should be merged with the ports of the base class,s
  // using BtActionNode::providedBasicPorts()
  static PortsList providedPorts() {
    return providedBasicPorts({InputPort<unsigned>("order")});
  }

  // This is called when the TreeNode is ticked and it should
  // send the request to the action server
  bool setGoal(BtActionNode::Goal& goal) override {
    // get "order" from the Input port
    getInput("order", goal.order);
    // return true, if we were able to set the goal correctly.
    return true;
  }

  // Callback executed when the reply is received.
  // Based on the reply you may decide to return SUCCESS or FAILURE.
  NodeStatus onResultReceived(const WrappedResult& wr) override {
    std::stringstream ss;
    ss << "Result received: ";
    for (auto number : wr.result->sequence) {
      ss << number << " ";
    }
    RCLCPP_INFO(node_->get_logger(), ss.str().c_str());
    return NodeStatus::SUCCESS;
  }

  // Callback invoked when there was an error at the level
  // of the communication between client and server.
  // This will set the status of the TreeNode to either SUCCESS or FAILURE,
  // based on the return value.
  // If not overridden, it will return FAILURE by default.
  virtual NodeStatus onFailure(ActionNodeErrorCode error) override {
    RCLCPP_ERROR(node_->get_logger(), "Error: %d", error);
    return NodeStatus::FAILURE;
  }

  // we also support a callback for the feedback, as in
  // the original tutorial.
  // Usually, this callback should return RUNNING, but you
  // might decide, based on the value of the feedback, to abort
  // the action, and consider the TreeNode completed.
  // In that case, return SUCCESS or FAILURE.
  // The Cancel request will be send automatically to the server.
  NodeStatus onFeedback(const std::shared_ptr<const Feedback> feedback) {
    std::stringstream ss;
    ss << "Next number in sequence received: ";
    for (auto number : feedback->partial_sequence) {
      ss << number << " ";
    }
    RCLCPP_INFO(node_->get_logger(), ss.str().c_str());
    return NodeStatus::RUNNING;
  }
};

*/
