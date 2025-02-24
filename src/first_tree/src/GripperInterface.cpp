#include "GripperInterface.h"

using namespace BT;
using namespace std;

GripperInterface::GripperInterface() : _open(true) {}

NodeStatus GripperInterface::open() {
  _open = true;
  cout << "GripperInterface::open" << endl;
  return NodeStatus::SUCCESS;
}

NodeStatus GripperInterface::close() {
  cout << "GripperInterface::close" << endl;
  _open = false;
  return NodeStatus::SUCCESS;
}
