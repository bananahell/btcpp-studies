#include "publisher_node.h"

using namespace std;
using namespace rclcpp;
using namespace BT;
using namespace std_msgs::msg;

PublisherNode::PublisherNode(const string &xmlTagName,
                             const NodeConfiguration &conf,
                             Node::SharedPtr nodePtr)
    : SyncActionNode(xmlTagName, conf) {
  string topic = "bt_pubsub/sub";
  SystemDefaultsQoS qos = SystemDefaultsQoS();
  qos.best_effort();
  strPublisherPtr_ = nodePtr->create_publisher<String>(topic, qos);
}

NodeStatus PublisherNode::tick() {
  String strMsg;
  Optional<string> msg = getInput<string>("message");
  Optional<int> numInput = getInput<int>("number");
  int timesToSend = numInput.value();
  strMsg.data = msg.value();
  for (int i = 0; i < timesToSend; i++) {
    strPublisherPtr_->publish(strMsg);
  }
  return NodeStatus::SUCCESS;
}

PortsList PublisherNode::providedPorts() {
  return PortsList{InputPort<string>("message"), InputPort<int>("number")};
}
