#include "../include/calcrotationtask.h"
#include "../../include\treecontext.h"

#include "../../../include/componentmessages.h"
#include "../../../include/entity.h"

#include "../../../../Ugine/include/math.h"

void CalculateRotationTask::Init()
{
	MessageGetAngularSpeed msgGAngularSpeed;
	owner->ReciveMessage(&msgGAngularSpeed);
	angularSpeed = msgGAngularSpeed.o_speed;
	isInitialized = true;
}

ITreeNode::TResult CalculateRotationTask::Run()
{
	TResult ret = E_SUCCESS;
	Entity * enemy;
	double angle, rotationAngle;
	context->GetValueEntity(TreeContext::KEY_THREAT, &enemy);
	angle=Angle(owner->x, owner->y, enemy->x, enemy->y);
	angle = angle - 90;
	if (angle<45 && angle>-45) {
		if (angle > 0) {
			if (owner->rotation > 0 && owner->rotation <= 90) {
				rotationAngle = Angle(owner->x - owner->width / 2, owner->y - owner->height / 2, enemy->x+enemy->width / 2, enemy->y+enemy->height/2);
			}else if (owner->rotation > 90 && owner->rotation <= 180) {
				rotationAngle = Angle(owner->x + owner->width / 2, owner->y - owner->height / 2, enemy->x - enemy->width / 2, enemy->y + enemy->height / 2);
			}
			else if (owner->rotation > 180 && owner->rotation <= 270) {
				rotationAngle = Angle(owner->x + owner->width / 2, owner->y + owner->height / 2, enemy->x - enemy->width / 2, enemy->y - enemy->height / 2);
			}
			else if (owner->rotation > 270 && owner->rotation <= 360) {
				rotationAngle = Angle(owner->x + owner->width / 2, owner->y - owner->height / 2, enemy->x - enemy->width / 2, enemy->y + enemy->height / 2);
			}
		}
		else {
			if (owner->rotation > 0 && owner->rotation <= 90) {
				rotationAngle = Angle(owner->x + owner->width / 2, owner->y - owner->height / 2, enemy->x - enemy->width / 2, enemy->y + enemy->height / 2);
			}
			else if (owner->rotation > 90 && owner->rotation <= 180) {
				rotationAngle = Angle(owner->x - owner->width / 2, owner->y - owner->height / 2, enemy->x + enemy->width / 2, enemy->y + enemy->height / 2);
			}
			else if (owner->rotation > 180 && owner->rotation <= 270) {
				rotationAngle = Angle(owner->x - owner->width / 2, owner->y + owner->height / 2, enemy->x + enemy->width / 2, enemy->y - enemy->height / 2);
			}
			else if (owner->rotation > 270 && owner->rotation <= 360) {
				rotationAngle = Angle(owner->x + owner->width / 2, owner->y + owner->height / 2, enemy->x - enemy->width / 2, enemy->y - enemy->height / 2);
			}
		}
		rotationAngle -= 90;
	}
	else {
		rotationAngle = 0;
	}
	context->SetValueDouble(TreeContext::KEY_ROTATION, rotationAngle);
	return ret;
}
