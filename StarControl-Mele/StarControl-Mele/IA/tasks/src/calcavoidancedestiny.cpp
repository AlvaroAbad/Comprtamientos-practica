#include "..\include\calcavoidancedestiny.h"
#include "../../include\treecontext.h"

#include "../../../include/componentmessages.h"
#include "../../../include/entity.h"

#include "../../../../Ugine/include/math.h"
void CalculateAvoidanceDestiny::Init()
{
	MessageGetLinearSpeed msgGLinearSpeed;
	owner->ReciveMessage(&msgGLinearSpeed);
	linearSpeed = msgGLinearSpeed.o_speed;
	isInitialized = true;
}

ITreeNode::TResult CalculateAvoidanceDestiny::Run()
{
	Entity * enemy;
	context->GetValueEntity(TreeContext::KEY_THREAT, &enemy);

	Vec2D direction, threat;
	float projection;
	direction.x = DegCos(owner->rotation - 90)*linearSpeed;
	direction.y = DegSin(owner->rotation - 90)*-linearSpeed;

	threat.x = enemy->x - owner->x;
	threat.y = enemy->y - owner->y;

	projection=threat.Dot(direction);

	direction.normalize();


	
	return TResult();
}
