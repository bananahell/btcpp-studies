#include <behaviortree_cpp_v3/bt_factory.h>

#include "ApproachObject.h"
#include "GripperInterface.h"

using namespace BT;
using namespace std;

static const char* xml_text = R"(
<root BTCPP_format="4" >
  <BehaviorTree ID="MainTree">
    <Sequence name="root_sequence">
      <CheckBattery   name="battery_ok"/>
      <OpenGripper    name="open_gripper"/>
      <ApproachObject name="approach_object"/>
      <CloseGripper   name="close_gripper"/>
    </Sequence>
  </BehaviorTree>
</root>
)";

NodeStatus CheckBattery() {
  cout << "[ Battery: OK ]" << endl;
  return NodeStatus::SUCCESS;
}

int main() {
  BehaviorTreeFactory factory;
  factory.registerNodeType<ApproachObject>("ApproachObject");
  factory.registerSimpleCondition("CheckBattery",
                                  [&](TreeNode&) { return CheckBattery(); });
  GripperInterface gripper;
  factory.registerSimpleAction("OpenGripper",
                               [&](TreeNode&) { return gripper.open(); });
  factory.registerSimpleAction("CloseGripper",
                               [&](TreeNode&) { return gripper.close(); });
  Tree tree = factory.createTreeFromText(xml_text);
  tree.tickRootWhileRunning();
  return 0;
}
