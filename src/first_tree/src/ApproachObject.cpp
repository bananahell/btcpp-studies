#include "ApproachObject.h"

using namespace BT;
using namespace std;

ApproachObject::ApproachObject(const string& name) : SyncActionNode(name, {}) {}

NodeStatus ApproachObject::tick() {
  cout << "ApproachObject: " << this->name() << endl;
  return NodeStatus::SUCCESS;
}
