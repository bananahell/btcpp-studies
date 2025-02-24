#include <behaviortree_cpp_v3/bt_factory.h>

class GripperInterface {
 public:
  GripperInterface();

  BT::NodeStatus open();

  BT::NodeStatus close();

 private:
  bool _open;
};
