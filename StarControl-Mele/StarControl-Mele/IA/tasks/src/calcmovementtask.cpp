#include "..\include\calcMovementtask.h"
#include "../../include\treecontext.h"

#include "../../../include/componentmessages.h"
#include "../../../include/entity.h"

#include "../../../../Ugine/include/math.h"
void CalculateMovementTask::Init()
{
	MessageGetLinearSpeed msgGLinearSpeed;
	owner->ReciveMessage(&msgGLinearSpeed);
	linearSpeed = msgGLinearSpeed.o_speed;
	isInitialized = true;
}

ITreeNode::TResult CalculateMovementTask::Run()
{
	double rotationAngle;
	Entity * enemy;
	context->GetValueDouble(TreeContext::KEY_ROTATION, &rotationAngle);
	context->GetValueEntity(TreeContext::KEY_THREAT, &enemy);
	rotationAngle += owner->rotation;
	double slope, b;
	double speedX, speedY;
	double cornerX, cornerY, enemyCornerX, enemyCornerY;
	double destX, destY;
	double incX, incY;

	if (rotationAngle > 0 && rotationAngle <= 90) {
		cornerX = owner->x - owner->width / 2;
		cornerY = owner->y + owner->height / 2;
		enemyCornerX = enemy->x - enemy->width / 2;
		enemyCornerY= enemy->y + enemy->height / 2;
		destX= owner->width / 2;
		destY= -owner->height / 2;
	}
	else if (rotationAngle > 90 && rotationAngle <= 180) {
		cornerX = owner->x + owner->width / 2;
		cornerY = owner->y + owner->height / 2;
		enemyCornerX = enemy->x + enemy->width / 2;
		enemyCornerY = enemy->y + enemy->height / 2;
		destX = -owner->width / 2;
		destY = -owner->height / 2;
	}
	else if (rotationAngle > 180 && rotationAngle <= 270) {
		cornerX = owner->x + owner->width / 2;
		cornerY = owner->y - owner->height / 2;
		enemyCornerY = enemy->y - enemy->height / 2 +1;
		destX = -owner->width / 2;
		destY = owner->height / 2;
	}
	else if (rotationAngle > 270 && rotationAngle <= 360) {
		cornerX = owner->x - owner->width / 2;
		cornerY = owner->y - owner->height / 2;
		enemyCornerX = enemy->x - enemy->width / 2;
		enemyCornerY = enemy->y - enemy->height / 2;
		destX = owner->width / 2;
		destY = owner->height / 2;
	}
	speedX = DegCos(rotationAngle - 90)*linearSpeed;
	speedY = DegSin(rotationAngle - 90)*-linearSpeed;
	slope = (cornerY - (cornerY + speedY)) / ((cornerX + speedX) - cornerX);
	b = -cornerX - slope*cornerX;
	destY+= enemyCornerY+1

}
