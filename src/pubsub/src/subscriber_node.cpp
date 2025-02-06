#include "subscriber_node.h"

using namespace std;
using namespace std::chrono;
using namespace std::placeholders;
using namespace rclcpp;
using namespace BT;
using namespace std_msgs::msg;

SubscriberNode::SubscriberNode(const string &xmlTagName,
                               const NodeConfiguration &conf,
                               Node::SharedPtr nodePtr)
    : ConditionNode(xmlTagName, conf) {
  string topic = "bt_pubsub/sub";
  SystemDefaultsQoS qos = SystemDefaultsQoS();
  qos.best_effort();
  strSubscriberPtr_ = nodePtr->create_subscription<String>(
      topic, qos, bind(&SubscriberNode::updateMsg, this, _1));
}

void SubscriberNode::updateMsg(const String::SharedPtr newMsg) {
  transform(newMsg->data.begin(), newMsg->data.end(), newMsg->data.begin(),
            ::toupper);
  msg_ = newMsg->data;
}

bool SubscriberNode::waitForMessage(int waitDuration) {
  WaitSet waitSet;
  waitSet.add_subscription(strSubscriberPtr_);
  WaitResult ret = waitSet.wait(seconds(waitDuration));
  if (ret.kind() == WaitResultKind::Ready) {
    String msg;
    MessageInfo info;
    bool retTake = strSubscriberPtr_->take(msg, info);
    return retTake;
  }
  return false;
}

NodeStatus SubscriberNode::tick() {
  Optional<int> waitDurationSec = getInput<int>("wait_duration_sec");
  int waitDuration = waitDurationSec.value();
  bool receivedMsg = waitForMessage(waitDuration);
  if (msg_.empty() || !receivedMsg) {
    return NodeStatus::FAILURE;
  }
  setOutput("message", msg_);
  return NodeStatus::SUCCESS;
}

PortsList SubscriberNode::providedPorts() {
  return PortsList{OutputPort<string>("message"),
                   InputPort<int>("wait_duration_sec")};
}
