#include <behaviortree_cpp_v3/bt_factory.h>

class ThinkWhatToSay : public BT::SyncActionNode {
 public:
  ThinkWhatToSay(const std::string&, const BT::NodeConfiguration&);

  static BT::PortsList providedPorts();

  BT::NodeStatus tick() override;
};
