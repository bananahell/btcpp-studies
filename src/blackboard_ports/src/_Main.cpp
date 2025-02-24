#include <behaviortree_cpp_v3/bt_factory.h>

#include <filesystem>

#include "SaySomething.h"
#include "ThinkWhatToSay.h"

using namespace BT;
using namespace std;

int main() {
  string btLocation = "./src/blackboard_ports/behavior_trees/tell_answer.xml";
  BehaviorTreeFactory factory;
  factory.registerNodeType<SaySomething>("SaySomething");
  factory.registerNodeType<ThinkWhatToSay>("ThinkWhatToSay");
  Tree tree = factory.createTreeFromFile(btLocation);
  tree.tickRootWhileRunning();
  return 0;
}
