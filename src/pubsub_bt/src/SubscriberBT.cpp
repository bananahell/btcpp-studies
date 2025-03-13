#include "SubscriberBT.h"

#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace BT;
using namespace rclcpp;
using namespace std_msgs::msg;

SubscriberBT::SubscriberBT(const string &xmlTagName,
                           const NodeConfiguration &conf,
                           Node::SharedPtr nodePtr)
    : ConditionNode(xmlTagName, conf) {
  string topic = "hello";
  SystemDefaultsQoS qos = SystemDefaultsQoS();
  qos.best_effort();
  CallbackGroup::SharedPtr callbackGroup =
      nodePtr->create_callback_group(CallbackGroupType::Reentrant, false);
  SubscriptionOptions options;
  options.callback_group = callbackGroup;
  strSubscriberPtr_ = nodePtr->create_subscription<String>(
      topic, qos, bind(&SubscriberBT::updateMsg, this, placeholders::_1),
      options);
}

NodeStatus SubscriberBT::tick() {
  Optional<int> waitDurationSec = getInput<int>("wait_duration_sec");
  int waitDuration = waitDurationSec.value();
  bool receivedMsg = waitForMessage(waitDuration);
  if (msg_.empty() || !receivedMsg) {
    return NodeStatus::FAILURE;
  }
  setOutput("message", msg_);
  return NodeStatus::SUCCESS;
}

PortsList SubscriberBT::providedPorts() {
  return PortsList{OutputPort<string>("message"),
                   InputPort<int>("wait_duration_sec")};
}

void SubscriberBT::updateMsg(const String::SharedPtr newMsg) {
  msg_ = newMsg->data;
}

bool SubscriberBT::waitForMessage(int waitDuration) {
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
