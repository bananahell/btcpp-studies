#include <behaviortree_cpp_v3/bt_factory.h>

class ApproachObject : public BT::SyncActionNode {
 public:
  ApproachObject(const std::string&);

  BT::NodeStatus tick() override;
};
