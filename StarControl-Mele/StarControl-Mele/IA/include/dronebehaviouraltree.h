#ifndef SCM_IA_DRONEBEHAVIORALTREE_H
#define SCM_IA_DRONEBEHAVIORALTREE_H
#include "treecontext.h"
#include "behaviouraltree.h"
class ITreeNode;
class Entity;
class DroneBehaviouralTree: public ABehaviouralTree
{
public:
	DroneBehaviouralTree(Entity * Owner);
	void Run();
};
#endif // !SCM_IA_DRONEBEHAVIORALTREE_H
