#ifndef SCM_GAMECOMPONENTS_H
#define SCM_GAMECOMPONENTS_H
#include "component.h"
#include "componentmessages.h"
#include "../../InputManager/include/iregistrable.h"

#pragma region COMPONENT_RENDERER
class Image;

class ComponentRenderer : public Component
{
public:
	ComponentRenderer(Image * render, unsigned int frames = 1, unsigned int frameRate = 0,bool loop=true)
		:render(render), frames(frames), frameRate(frameRate), loop(loop) {
		actualFrame = 0;
	}
	virtual ~ComponentRenderer() {};

	virtual void Update(float elapsed);
	virtual void ReciveMessage(Message * message);

private:
	Image * render;
	unsigned int frames, frameRate;
	float actualFrame;
	bool loop;
};
#pragma endregion insert when entity Has a visual representation on screen

#pragma region COMPONENT_PLAYER_CONTROLLER
class ComponentPlayerController : public Component, IRegistrable
{
public:
	enum direction {
		D_FORWARD=-1,
		D_BACKWARDS=1,
		D_LEFT=1,
		D_RIGHT=-1,
		D_HOLD=0
	};
	ComponentPlayerController(double linearSpeed, double angularSpeed)
		:linearSpeed(linearSpeed), angularSpeed(angularSpeed) {
		movement = rotation = D_HOLD;
	};
	virtual ~ComponentPlayerController() {}
	virtual void Update(float elapsed);
	virtual void ReciveMessage(Message * message);
	virtual void BinKeys(inputs forward, inputs backwards, inputs rotateLeft, inputs rotateRight);
	virtual void OnEvent(const Event *action);
private:
	virtual void Register(inputs key, inputs action);
	virtual void Unregister(inputs key, inputs action);
	virtual void Unregister();

	direction movement, rotation;
	inputs forward, backwards, rotateLeft, rotateRight;
	double linearSpeed, angularSpeed;
};
#pragma endregion insert when entity is controlled by user

#pragma region COMPONENT_STATS
class ComponentStats : public Component {
public:
	ComponentStats(float life, float maxEnergy, float EneryRegeneration)
		:life(life), maxEnergy(maxEnergy), 
		actualEnergy(maxEnergy), EneryRegeneration(EneryRegeneration){};
	virtual ~ComponentStats() {};
	virtual void Update(float elapsed);
	virtual void ReciveMessage(Message * message);
private:
	float life, maxEnergy,actualEnergy, EneryRegeneration;
};
#pragma endregion insert when entity Has life and energy stats

#pragma region COMPONENT_CIRCLECOLLISION
class CircleCollision;
class ComponentCircleCollision: public Component
{
public:
	ComponentCircleCollision(double damageDeal,bool destroyUponCollision);

	virtual void Update(float elapsed);
	virtual void ReciveMessage(Message * message);

	virtual ~ComponentCircleCollision();

private:
	CircleCollision * collider;
	double x, y, radius;
	double damageDeal;
	bool didCollide,destroyUponCollision;
	Entity * collisionEntity;
};
#pragma endregion insert when entity needs to collide with other entities

#pragma region COMPONENT_SHIPEXPLOSION
class EntityFactory;
class ComponentShipExplosion: public Component {
public:
	ComponentShipExplosion(EntityFactory * factory) :factory(factory) {}
	virtual void Update(float elapsed) {};
	virtual void ReciveMessage(Message * message);
private:
	EntityFactory * factory;
};
#pragma endregion insert when entity needs has a ship Explosion animation

#pragma region COMPONENT_MISSILEWEAPON
class ComponentMissileWeapon : public Component {
public:
	ComponentMissileWeapon() {}
	virtual ~ComponentMissileWeapon() {}
	virtual void Update(float elapsed) {};
	virtual void ReciveMessage(Message * message) {};
private:
};
#pragma endregion insert when entity has a missile weapon
#endif // !SCM_GAMECOMPONENTS_H

