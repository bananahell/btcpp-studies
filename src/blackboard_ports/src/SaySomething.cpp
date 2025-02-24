#include "SaySomething.h"

using namespace BT;
using namespace std;

SaySomething::SaySomething(const string& name, const NodeConfiguration& config)
    : SyncActionNode(name, config) {}

PortsList SaySomething::providedPorts() {
  return {InputPort<string>("message")};
}

NodeStatus SaySomething::tick() {
  Optional<string> msg = getInput<string>("message");
  if (!msg) {
    throw RuntimeError("missing required input [message]: ", msg.error());
  }
  cout << "Robot says: " << msg.value() << endl;
  return NodeStatus::SUCCESS;
}
