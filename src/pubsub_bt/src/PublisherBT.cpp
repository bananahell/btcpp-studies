#include "PublisherBT.h"

#include <chrono>

using namespace std;
using namespace BT;
using namespace rclcpp;
using namespace std_msgs::msg;

PublisherBT::PublisherBT(const string &xmlTagName,
                         const NodeConfiguration &conf, Node::SharedPtr nodePtr)
    : SyncActionNode(xmlTagName, conf) {
  string topic = "hello";
  SystemDefaultsQoS qos = SystemDefaultsQoS();
  qos.best_effort();
  CallbackGroup::SharedPtr callbackGroup =
      nodePtr->create_callback_group(CallbackGroupType::Reentrant);
  PublisherOptions options;
  options.callback_group = callbackGroup;
  strPublisherPtr_ = nodePtr->create_publisher<String>(topic, qos, options);
}

NodeStatus PublisherBT::tick() {
  String strMsg;
  Optional<string> msg = getInput<string>("message");
  strMsg.data = msg.value();
  strPublisherPtr_->publish(strMsg);
  sleep(1);
  strPublisherPtr_->publish(strMsg);
  sleep(1);
  strPublisherPtr_->publish(strMsg);
  sleep(1);
  strPublisherPtr_->publish(strMsg);
  sleep(1);
  strPublisherPtr_->publish(strMsg);
  return NodeStatus::SUCCESS;
}

PortsList PublisherBT::providedPorts() {
  return PortsList{InputPort<string>("message")};
}
