#ifndef SCM_ENTITYCOMPONENTS_H
#define SCM_ENTITYCOMPONENTS_H
#include "component.h"
#include "componentmessages.h"

#include "../../InputManager/include/iregistrable.h"

#include "../../Ugine/include/array.h" 

#pragma region COMPONENT_RENDERER
class Image;
class World;
enum Weapons_Type {
	WT_MAIN,
	WT_SECONDARY
};
class ComponentRenderer : public Component
{
public:
	ComponentRenderer(Image * render, unsigned int firstFrame = 0, unsigned int frames = 1, unsigned int frameRate = 0,bool loop=true)
		:render(render), firstFrame(firstFrame), frames(frames), frameRate(frameRate), loop(loop) {
		actualFrame = 0;
	}
	virtual ~ComponentRenderer() {};

	virtual void Update(float elapsed);
	virtual void ReciveMessage(Message * message);

private:
	Image * render;
	unsigned int firstFrame, frames, frameRate;
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
		D_LEFT=-1,
		D_RIGHT=1,
		D_HOLD=0
	};
	ComponentPlayerController(double linearSpeed, double angularSpeed)
		:linearSpeed(linearSpeed), angularSpeed(angularSpeed) {
		movement = rotation = D_HOLD;
	};
	virtual ~ComponentPlayerController() {}
	virtual void Update(float elapsed);
	virtual void ReciveMessage(Message * message);
	virtual void BinKeys(inputs forward, inputs backwards, inputs rotateLeft, inputs rotateRight, inputs mainFire, inputs secondFire);
	virtual void OnEvent(const Event *action);
private:
	virtual void Register(inputs key, inputs action);
	virtual void Unregister(inputs key, inputs action);
	virtual void Unregister();

	direction movement, rotation;
	inputs forward, backwards, rotateLeft, rotateRight, mainFire, secondFire;
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

#pragma region COMPONENT_SMALLXPLOSION
class EntityFactory;
class ComponentSmallExplosion : public Component {
public:
	ComponentSmallExplosion(EntityFactory * factory) :factory(factory) {}
	virtual ~ComponentSmallExplosion() {};
	virtual void Update(float elapsed) {};
	virtual void ReciveMessage(Message * message);
private:
	EntityFactory * factory;
};
#pragma endregion insert when entity needs has a small Explosion animation

#pragma region COMPONENT_LINEARMOVEMENT
class ComponentLinearMovement : public Component {
public:
	ComponentLinearMovement(double linearSpeed):linearSpeed(linearSpeed){};
	virtual ~ComponentLinearMovement() {};
	virtual void Update(float elapsed);
	virtual void ReciveMessage(Message * message) {};
private:
	double linearSpeed;
};
#pragma endregion insert when entity has a simple linear movement

#pragma region COMPONENT_BEHAVIOUR
class ABehaviouralTree;
class ComponentBehaviour : public Component {
public:
	ComponentBehaviour(ABehaviouralTree * behaviour) :behaviour(behaviour) {};
	virtual ~ComponentBehaviour() {};
	virtual void Update(float elapsed);
	virtual void ReciveMessage(Message * message) {};
private:
	ABehaviouralTree *behaviour;
};
#pragma endregion insert when entity is control by the IA

#pragma region COMPONENT_SENSOR
class ComponentSensor : public Component {
public:
	ComponentSensor(double lookAhead, double fieldOfView) :lookAhead(lookAhead), fieldOfView(fieldOfView) {};
	virtual ~ComponentSensor(){};
	virtual void Update(float elapsed);
	virtual void ReciveMessage(Message * message) {};
private:
	double lookAhead;
	double fieldOfView;
};
#pragma endregion insert when entity has a Sensor

#pragma region COMPONENT_MODULARWEAPON
class ComponentModularWeapon : public Component {
public:
	ComponentModularWeapon() :ready(true) {};
	virtual ~ComponentModularWeapon();
	virtual void Update(float elapsed);
	virtual void ReciveMessage(Message * message);
private:
	Weapons_Type type;
	bool ready;
	Array<Component *> components;
};
#pragma endregion insert when entity needs a modular weapon

#pragma region COMPONENT_BALISTICWEAPON
class ComponentBalisticWeapon : public Component {
public:
	ComponentBalisticWeapon(World * world, EntityFactory * factory,Weapons_Type type, double coolDown, double damage, double energyConsumption, double speed)
		:ready(true), world(world), factory(factory), type(type), coolDown(coolDown), damage(damage), energyConsumption(energyConsumption), speed(speed){};
	virtual ~ComponentBalisticWeapon() {};
	virtual void Update(float elapsed);
	virtual void ReciveMessage(Message * message);
private:
	Weapons_Type type;
	bool ready;
	double coolDown, damage, energyConsumption, speed;
	float currentCoolDown;
	EntityFactory * factory;
	World * world;
};
#pragma endregion insert when entity needs a ballistic weapon

#pragma region COMPONENT_LASERWEAPON
class ComponentLaserWeapon : public Component {
public:
	ComponentLaserWeapon(World * world, Weapons_Type type, double coolDown, double damage, double energyConsumption, double range)
		:ready(true), world(world), type(type), coolDown(coolDown), damage(damage), energyConsumption(energyConsumption), range(range) {};
	virtual ~ComponentLaserWeapon() {};
	virtual void Update(float elapsed);
	virtual void ReciveMessage(Message * message);
private:
	Weapons_Type type;
	bool ready;
	double coolDown, damage, energyConsumption, range;
	float currentCoolDown;
	World * world;
};
#pragma endregion insert when entity needs a laser weapon
#endif // !SCM_ENTITYCOMPONENTS_H

