#include "behaviortree_cpp_v3/bt_factory.h"

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

class ApproachObject : public BT::SyncActionNode {
 public:
  ApproachObject(const std::string& name) : BT::SyncActionNode(name, {}) {}

  BT::NodeStatus tick() override {
    std::cout << "ApproachObject: " << this->name() << std::endl;
    return BT::NodeStatus::SUCCESS;
  }
};

BT::NodeStatus CheckBattery() {
  std::cout << "[ Battery: OK ]" << std::endl;
  return BT::NodeStatus::SUCCESS;
}

class GripperInterface {
 public:
  GripperInterface() : _open(true) {}

  BT::NodeStatus open() {
    _open = true;
    std::cout << "GripperInterface::open" << std::endl;
    return BT::NodeStatus::SUCCESS;
  }

  BT::NodeStatus close() {
    std::cout << "GripperInterface::close" << std::endl;
    _open = false;
    return BT::NodeStatus::SUCCESS;
  }

 private:
  bool _open;
};

int main() {
  BT::BehaviorTreeFactory factory;
  factory.registerNodeType<ApproachObject>("ApproachObject");
  factory.registerSimpleCondition(
      "CheckBattery", [&](BT::TreeNode&) { return CheckBattery(); });
  GripperInterface gripper;
  factory.registerSimpleAction("OpenGripper",
                               [&](BT::TreeNode&) { return gripper.open(); });
  factory.registerSimpleAction("CloseGripper",
                               [&](BT::TreeNode&) { return gripper.close(); });
  auto tree = factory.createTreeFromText(xml_text);
  tree.tickRootWhileRunning();
  return 0;
}

/* Expected output:
*
       [ Battery: OK ]
       GripperInterface::open
       ApproachObject: approach_object
       GripperInterface::close
*/
