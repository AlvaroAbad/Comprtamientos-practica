#include "..\include\dronebehaviouraltree.h"
#include "../include/selectornode.h"
#include "../include/sequencenode.h"
#include "../tasks/include/checkthreattask.h"
#include "../tasks/include/calcrotationtask.h"
DroneBehaviouralTree::DroneBehaviouralTree(Entity * Owner)
{
	root = new SelectorNode()//Selector
		->AddNode(
			new SequenceNode()//Avoidance Sequence
			->AddNode(
				new CheckTHreatTask(Owner,&context))
			->AddNode(
				new CalculateRotationTask(Owner, &context)));
}

void DroneBehaviouralTree::Run()
{
	if (!root->initialized()) {
		root->Init();
	}
	root->Run();
}
