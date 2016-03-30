#include "../include/entitycomponents.h"
#include "../include/entity.h"
#include "../include/entityfactory.h"

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
		actualFrame = 0;
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
	father->rotation += angularSpeed*elapsed*rotation;
	double velX, velY;
	velX = DegCos(90 - father->rotation)*linearSpeed;
	velY = DegSin(90 - father->rotation)*linearSpeed;
	father->x += velX*elapsed*movement;
	father->y += velY*elapsed*movement;
	rotation = D_HOLD;
	movement = D_HOLD;
}
void ComponentPlayerController::ReciveMessage(Message * message)
{
}

void ComponentPlayerController::BinKeys(inputs forward, inputs backwards, inputs rotateLeft, inputs rotateRight)
{
	this->forward = forward;
	Register(forward, inputs::KEY_PRESSED_DOWN);
	this->backwards = backwards;
	Register(backwards, inputs::KEY_PRESSED_DOWN);
	this->rotateLeft = rotateLeft;
	Register(rotateLeft, inputs::KEY_PRESSED_DOWN);
	this->rotateRight = rotateRight;
	Register(rotateRight, inputs::KEY_PRESSED_DOWN);
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
	MessageGetTransform msgGTransform;
	father->ReciveMessage(&msgGTransform);
	x = msgGTransform.x;
	y = msgGTransform.y;
	radius = (msgGTransform.height > msgGTransform.width ? msgGTransform.height / 2 : msgGTransform.width / 2);
	if (didCollide) {
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
		//MessageExplode * msgExplode = static_cast<MessageExplode *>(message);
		CASTMESSAGE(MessageExplode)
			msg->entity = factory->CreateShipExplosion(father->x, father->y);
	}
}
#pragma endregion insert when entity needs has a ship Explosion animation

#pragma region COMPONENT_WEAPON
ComponentWeapon::~ComponentWeapon()
{
	for (size_t i = 0; i < components.Size(); i++)
	{
		delete components[i];
	}
}

void ComponentWeapon::Update(float elapsed)
{
	for (size_t i = 0; i < components.Size(); i++)
	{
		components[i]->Update(elapsed);
	}
}

void ComponentWeapon::ReciveMessage(Message * message)
{
	if (message->type == Message::MSG_WEAPONREADY) {
		ready = true;
	}
	else if (message->type == Message::MSG_FIRE) {
		ready = false;
		for (size_t i = 0; i < components.Size(); i++)
		{
			components[i]->ReciveMessage(message);
		}
	}
	
}
#pragma endregion insert when entity needs a weapon

