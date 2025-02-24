#include "ThinkWhatToSay.h"

using namespace BT;
using namespace std;

ThinkWhatToSay::ThinkWhatToSay(const string& name,
                               const NodeConfiguration& config)
    : SyncActionNode(name, config) {}

PortsList ThinkWhatToSay::providedPorts() {
  return {OutputPort<string>("text")};
}

NodeStatus ThinkWhatToSay::tick() {
  setOutput("text", "The answer is 42");
  return NodeStatus::SUCCESS;
}
