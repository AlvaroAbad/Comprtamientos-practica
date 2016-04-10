#include "../include/checkthreattask.h"
#include "../../include\treecontext.h"

#include "../../../include/componentmessages.h"
#include "../../../include/entity.h"
void CheckTHreatTask::Init()
{
	isInitialized = true;
}

ITreeNode::TResult CheckTHreatTask::Run()
{
	TResult ret = E_FAIL;
	MessegGetColsestEnemy msgGCEnemy;
	msgGCEnemy.o_enemie = nullptr;
	owner->ReciveMessage(&msgGCEnemy);
	if (!msgGCEnemy.o_enemie) {
		context->SetValueEntity(TreeContext::KEY_THREAT, msgGCEnemy.o_enemie);
		context->SetValueDouble(TreeContext::KEY_ENEMYDISTANCE, msgGCEnemy.o_distance);
		ret = E_SUCCESS;
	}
	return ret;
}
