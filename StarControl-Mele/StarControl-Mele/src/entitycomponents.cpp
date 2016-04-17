#include "../include/entitycomponents.h"
#include "../include/entity.h"
#include "../include/entityfactory.h"
#include "../include/world.h"

#include "../IA/include/behaviouraltree.h"

#include "../../InputManager/include/managergameinterface.h"

#include "../../Ugine/include/math.h"
#include "../../Ugine/include/circlecollision.h"

#pragma warning(disable:4062)
#pragma warning(disable:4100)

#define CASTMESSAGE(MessageType) MessageType * msg =static_cast<MessageType *>(message);

#pragma region COMPONENT_RENDERER
void ComponentRenderer::Update(float elapsed)
{
	if (actualFrame <= frames - 1) {
		actualFrame += frameRate*elapsed;
	}
	else if (loop) {
		actualFrame = firstFrame;
	}
	else {
		father->dead = true;
	}
}

void ComponentRenderer::ReciveMessage(Message * message)
{
	if (message->type == Message::MSG_GRENDERING) {
		CASTMESSAGE(MessageGetRendering)
			msg->render = render;
		msg->frame = actualFrame;
	}
}

#pragma endregion insert when entity Has a visual representation on screen

#pragma region COMPONENT_PLAYER_CONTROLLER
void ComponentPlayerController::Update(float elapsed)
{
	father->rotation += angularSpeed*elapsed*-rotation;
	WrapValue(father->rotation, 360);
	double velX, velY;
	velX = DegCos(father->rotation - 90)*linearSpeed;
	velY = DegSin(father->rotation - 90)*-linearSpeed;
	father->x += velX*elapsed*movement;
	father->y += velY*elapsed*movement;
	rotation = D_HOLD;
	movement = D_HOLD;
}
void ComponentPlayerController::ReciveMessage(Message * message)
{
	if (message->type == Message::MSG_GETLINEARSPEED) {
		CASTMESSAGE(MessageGetLinearSpeed)
			msg->o_speed = linearSpeed;
	}
}

void ComponentPlayerController::BinKeys(inputs forward, inputs backwards, inputs rotateLeft,
	inputs rotateRight, inputs mainFire, inputs secondFire)
{
	this->forward = forward;
	Register(forward, inputs::KEY_PRESSED_DOWN);
	this->backwards = backwards;
	Register(backwards, inputs::KEY_PRESSED_DOWN);
	this->rotateLeft = rotateLeft;
	Register(rotateLeft, inputs::KEY_PRESSED_DOWN);
	this->rotateRight = rotateRight;
	Register(rotateRight, inputs::KEY_PRESSED_DOWN);
	this->mainFire = mainFire;
	Register(mainFire, inputs::KEY_PRESSED_DOWN);
	this->secondFire = secondFire;
	Register(mainFire, inputs::KEY_PRESSED_DOWN);
}

void ComponentPlayerController::Register(inputs key, inputs action)
{
	ManagerGameInterface::Register(this, key, action);
}

void ComponentPlayerController::Unregister(inputs key, inputs action)
{
	ManagerGameInterface::Unregister(this, key, action);
}

void ComponentPlayerController::Unregister()
{
	ManagerGameInterface::UnregisterAll(this);
}

void ComponentPlayerController::OnEvent(const Event * action)
{
	if (action->GetKey() == forward) {
		movement = static_cast<direction>(movement + D_FORWARD);
	}
	else if (action->GetKey() == backwards) {
		movement = static_cast<direction>(movement + D_BACKWARDS);
	}
	else if (action->GetKey() == rotateLeft) {
		rotation = static_cast<direction>(rotation + D_LEFT);
	}
	else if (action->GetKey() == rotateRight) {
		rotation = static_cast<direction>(rotation + D_RIGHT);
	}
	else if (action->GetKey() == mainFire) {
		MessageFire fire;
		fire.weapon = MessageFire::W_MAIN;
		father->ReciveMessage(&fire);
	}
	else if (action->GetKey() == secondFire) {
		MessageFire fire;
		fire.weapon = MessageFire::W_SECODARY;
		father->ReciveMessage(&fire);
	}
}
#pragma endregion insert when entity is controlled by user

#pragma region COMPONENT_STATS
void ComponentStats::Update(float elapsed)
{
	if (life <= 0) {
		father->dead = true;
	}
	if (actualEnergy < maxEnergy) {
		actualEnergy += EneryRegeneration*elapsed;
	}
	else {
		actualEnergy = maxEnergy;
	}
}

void ComponentStats::ReciveMessage(Message * message)
{
	switch (message->type)
	{
	case Message::MSG_GENERGY:
	{
		CASTMESSAGE(MessageGetEnergy)
			msg->energy = actualEnergy;
	}
	break;

	case Message::MSG_GLIFE:
	{
		CASTMESSAGE(MessageGetLife)
			msg->life = life;
	}
	break;

	case Message::MSG_REDUCEENERGY:
	{
		CASTMESSAGE(MessageReduceEnergy)
			actualEnergy -= msg->consumption;
	}
	break;

	case Message::MSG_REDUCELIFE:
	{
		CASTMESSAGE(MessageReduceLife)
			life -= msg->damage;
	}
	break;
	case Message::MSG_FIRE:
	{
		CASTMESSAGE(MessageFire)
			msg->CurrentEnergy = actualEnergy;
	}
	break;
	}
}

#pragma endregion insert when entity Has life and energy stats

#pragma region COMPONENT_CIRCLECOLLISION
ComponentCircleCollision::ComponentCircleCollision(double damageDeal, bool destroyUponCollision)
	:damageDeal(damageDeal), destroyUponCollision(destroyUponCollision)
{
	collider = new CircleCollision(&x, &y, &radius);
}

void ComponentCircleCollision::Update(float elapsed)
{
	x = father->x;
	y = father->y;
	radius = (father->height >  father->width ? father->height / 2 : father->width / 2);
	if (collisionEntity!=nullptr) {
		MessageReduceLife msgRLife;
		msgRLife.damage = damageDeal;
		collisionEntity->ReciveMessage(&msgRLife);
		didCollide = false;
		collisionEntity = nullptr;
		if (destroyUponCollision) {
			father->dead = true;
		}
	}
}

void ComponentCircleCollision::ReciveMessage(Message * message)
{
	switch (message->type)
	{
	case Message::MSG_CHECKCOLLISION:
	{
		CASTMESSAGE(MessageCheckCollision)
			MessageGetCollider msgGCollider;
		msgGCollider.collider = nullptr;
		msg->entity->ReciveMessage(&msgGCollider);
		if (msgGCollider.collider) {
			didCollide = msgGCollider.collider->DoesCollide(x, y, radius);
			if (didCollide) {
				collisionEntity = msg->entity;
				MessageAllertCollision msgAllertCollision;
				msgAllertCollision.entity = father;
				collisionEntity->ReciveMessage(&msgAllertCollision);
			}
		}
	}
	break;
	case Message::MSG_CHECKLASERCOLLISION:
	{
		CASTMESSAGE(MessageCheckLaserCollision)
			if (msg->laser->shooter != father) {
				double laserAngle, tAngle, rAngle, lAngle, bAngle;
				bool tHit, rHit, lHit, bHit;

				/*calcular colision por algebra*/
				float slope = (msg->laser->oY - msg->laser->dY) / (msg->laser->dX - msg->laser->oX);
				float b = -msg->laser->oY - slope*msg->laser->oX;
				float inverY = y*-1;
				float inverX = x*-1;
				float squearRadius = radius*radius;
				//printf("-----------------------------------\n");
				//printf("Slope: %f\n", slope);
				//printf("B: %f\n", b);
				//printf("Line: y=%fx+%f\n", slope, b);
				//printf("Circle: (x+%f)^2+(y+%f)^2=%f\n", inverX, inverY, squearRadius);
				//printf("despejar segmento de y:(y-%f)^2=%f-(x+%f)^2 \n", inverY, squearRadius, inverX);
				//printf("sustitucion:(%fx+%f-%f)^2=%f-(x+%f)^2 \n", slope, b, inverY, squearRadius, inverX);
				float bminvy = b - inverY;
				//printf("resolver:(%fx+%f)^2=%f-(x+%f)^2 \n", slope, bminvy, squearRadius, inverX);
				float squearSlope = slope*slope;
				float twoTimesSlopeTimesBmInvY = 2 * slope*(b - inverY);
				float SquearBmInvY = bminvy*bminvy;
				float twoTimesX = 2 * inverX;
				float squearX = inverX*inverX;
				//printf("resolver:%fx^2+%fx+%f=%f-(x^2+%fx+%f)\n", squearSlope, twoTimesSlopeTimesBmInvY, SquearBmInvY, squearRadius, twoTimesX, squearX);
				twoTimesX = twoTimesX*-1;
				squearX = squearX*-1;
				//printf("resolver:%fx^2+%fx+%f=%f-x^2+%fx+%f)\n", squearSlope, twoTimesSlopeTimesBmInvY, SquearBmInvY, squearRadius, twoTimesX, squearX);
				float SumSquearSlopeSquearX = squearSlope + 1;
				float sumTwoTimesSlopeTimesBmInvYTwoTimesX = twoTimesSlopeTimesBmInvY + (twoTimesX*-1);
				float sumSquearBmInvYSquearRadiusSquearX = SquearBmInvY + (squearRadius*-1) + squearX*-1;
				//printf("resolver:%fx^2+%fx+%f=0)\n", SumSquearSlopeSquearX, sumTwoTimesSlopeTimesBmInvYTwoTimesX, sumSquearBmInvYSquearRadiusSquearX);
				float formulaB = sumTwoTimesSlopeTimesBmInvYTwoTimesX*-1;
				float sqrFormulaB = formulaB*formulaB;
				float fourTimesFormulaATimesFormulaC = -4 * SumSquearSlopeSquearX*sumSquearBmInvYSquearRadiusSquearX;
				float twoTimesFormulaA = 2 * SumSquearSlopeSquearX;
				//printf("resolver:(%f+-sqrt(%f+%f))/%f\n", formulaB, sqrFormulaB, fourTimesFormulaATimesFormulaC, twoTimesFormulaA);
				float pointX1, pointX2, pointY1, pointY2, dist1, dist2, range;
				if (sqrFormulaB + fourTimesFormulaATimesFormulaC > 0 && twoTimesFormulaA != 0) {
					pointX1 = (formulaB + sqroot(sqrFormulaB + fourTimesFormulaATimesFormulaC)) / twoTimesFormulaA;
					pointX2 = (formulaB - sqroot(sqrFormulaB + fourTimesFormulaATimesFormulaC)) / twoTimesFormulaA;
					msg->hit = true;
					pointY1 = (slope*pointX1 + b)*-1;
					pointY2 = (slope*pointX2 + b)*-1;
					dist1 = Distance(msg->laser->oX, msg->laser->oY, pointX1, pointY1);
					dist2 = Distance(msg->laser->oX, msg->laser->oY, pointX2, pointY2);
					range = Distance(msg->laser->oX, msg->laser->oY, msg->laser->dX, msg->laser->dY);
					printf("oX:%f\noY: %f\n", pointX1, pointY1);
					if (Distance(msg->laser->oX, msg->laser->oY, pointX1, pointY1) < Distance(msg->laser->oX, msg->laser->oY, pointX2, pointY2)) {
						printf("X1:%f\nY1: %f\n", pointX1, pointY1);
						printf("dist1: %f\n", dist1);
						if (dist1 < range) {
							msg->hitX = pointX1;
							msg->hitY = pointY1;
						}
						else {
							msg->hit = false;
						}
					}
					else {
						printf("X2:%f\nY2: %f\n", pointX2, pointY2);
						printf("dist2: %f\n", dist2);
						if (dist2 < range) {
							msg->hitX = pointX2;
							msg->hitY = pointY2;
						}
						else {

							msg->hit = false;
						}
					}
				}
				else {
					msg->hit = false;
				}
				printf("-----------------------------------\n");
				/**/
			}
	}
	break;
	case Message::MSG_GCOLLIDER:
	{
		CASTMESSAGE(MessageGetCollider)
			msg->collider = collider;
	}
	break;
	case Message::MSG_ALERTCOLLISION:
	{
		CASTMESSAGE(MessageAllertCollision)
			didCollide = true;
		collisionEntity = msg->entity;
	}
	break;
	}
}

ComponentCircleCollision::~ComponentCircleCollision()
{
	delete collider;
}

#pragma endregion insert when entity needs to collide with other entities

#pragma region COMPONENT_SHIPEXPLOSION
void ComponentShipExplosion::ReciveMessage(Message * message)
{
	if (message->type == Message::MSG_EXPLODE) {
		CASTMESSAGE(MessageExplode)
			msg->entity = factory->CreateShipExplosion(father->x, father->y);
	}
}
#pragma endregion insert when entity needs has a ship Explosion animation

#pragma region COMPONENT_SMALLXPLOSION
void ComponentSmallExplosion::ReciveMessage(Message * message)
{
	if (message->type == Message::MSG_EXPLODE) {
		CASTMESSAGE(MessageExplode)
			msg->entity = factory->CreateSmallExplosion(father->x, father->y);
	}
}
#pragma endregion insert when entity needs has a small Explosion animation

#pragma region COMPONENT_LINEARMOVEMENT
void ComponentLinearMovement::Update(float elapsed)
{
	double velX, velY;
	velX = DegCos(father->rotation - 90)*-linearSpeed;
	velY = DegSin(father->rotation - 90)*linearSpeed;
	father->x += velX*elapsed;
	father->y += velY*elapsed;
}
#pragma endregion insert when entity has a simple linear movement

#pragma region COMPONENT_WEAPON
ComponentModularWeapon::~ComponentModularWeapon()
{
	for (size_t i = 0; i < components.Size(); i++)
	{
		delete components[i];
	}
}

void ComponentModularWeapon::Update(float elapsed)
{
	for (size_t i = 0; i < components.Size(); i++)
	{
		components[i]->Update(elapsed);
	}
}

void ComponentModularWeapon::ReciveMessage(Message * message)
{
	if (message->type == Message::MSG_WEAPONREADY) {
		ready = true;
	}
	else if (message->type == Message::MSG_FIRE) {
		CASTMESSAGE(MessageFire)
			if (ready) {
				msg->fire = true;
				msg->range = -1;
				msg->energyConsumption = -1;
				for (size_t i = 0; i < components.Size(); i++)
				{
					components[i]->ReciveMessage(message);
				}
				if (msg->fire) {
					MessageReduceEnergy msgREnergy;
					if (msg->energyConsumption > 0) {
						msgREnergy.consumption = msg->energyConsumption;
					}
					father->ReciveMessage(&msgREnergy);
					ready = false;
				}
			}
	}

}
#pragma endregion insert when entity needs a weapon

#pragma region COMPONENT_BALISTICWEAPON
void ComponentBalisticWeapon::Update(float elapsed)
{
	currentCoolDown -= elapsed;
	if (currentCoolDown <= 0) {
		currentCoolDown = 0;
		ready = true;
	}
	else {
		currentCoolDown -= elapsed;
	}
}

void ComponentBalisticWeapon::ReciveMessage(Message * message)
{
	if (message->type == Message::MSG_FIRE) {
		CASTMESSAGE(MessageFire)
			if (msg->CurrentEnergy > energyConsumption) {
				if (ready && msg->weapon == type) {
					double x, y;
					ready = false;
					currentCoolDown = coolDown;
					x = msg->x - DegCos(msg->rotation - 90)*(msg->width / 2);
					y = msg->y + DegSin(msg->rotation - 90)*(msg->height / 2);
					world->addEntity(factory->createMissile(damage, x, y, msg->rotation, speed));
					MessageReduceEnergy msgREnergy;
					msgREnergy.consumption = energyConsumption;
					father->ReciveMessage(&msgREnergy);
				}
			}
	}
}
#pragma endregion insert when entity has a ballistic weapon
#pragma region COMPONENT_LASERWEAPON
void ComponentLaserWeapon::Update(float elapsed)
{

	currentCoolDown -= elapsed;
	if (currentCoolDown <= 0) {
		currentCoolDown = 0;
		ready = true;
	}
	else {
		currentCoolDown -= elapsed;
	}
}

void ComponentLaserWeapon::ReciveMessage(Message * message)
{
	if (message->type == Message::MSG_FIRE) {
		CASTMESSAGE(MessageFire)
			if (msg->CurrentEnergy > energyConsumption) {
				if (ready && msg->weapon == type) {
					double oX, oY, dX, dY, rangeX, rangeY;
					ready = false;
					currentCoolDown = coolDown;
					oX = msg->x - DegCos(msg->rotation - 90)*((msg->width / 2) + 10);
					oY = msg->y + DegSin(msg->rotation - 90)*((msg->height / 2) + 10);
					rangeX = DegCos(msg->rotation - 90)*-range;
					rangeY = DegSin(msg->rotation - 90)*range;
					dX = oX + rangeX;
					dY = oY + rangeY;
					world->addLaserRender(World::Laser(oX, oY, dX, dY, damage, father));
					MessageReduceEnergy msgREnergy;
					msgREnergy.consumption = energyConsumption;
					father->ReciveMessage(&msgREnergy);
				}
			}
	}
}
#pragma endregion insert when entity has a laser weapon


#pragma region COMPONENT_BEHAVIOUR
void ComponentBehaviour::Update(float elapsed)
{
	behaviour->Run();
}
#pragma endregion insert when entity is control by the IA

#pragma region COMPONENT_SENSOR
void ComponentSensor::Update(float elapsed)
{
}
#pragma endregion insert when entity has a Sensor