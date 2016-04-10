#ifndef SCM_ENTITYFACTORY_H
#define SCM_ENTITYFACTORY_H

#include "../../Ugine/include/array.h"

class Entity;
class World;
class EntityFactory
{
public:
	EntityFactory() {};
	~EntityFactory() {};
	Entity * CreatePlayerOne(World * world);
	Entity * CreatePlayerTwo(World * world);
	Entity * CreateDrone(double x, double y, double rotation);
	Entity * CreateShipExplosion(double x, double y);
	Entity * CreateSmallExplosion(double x, double y);
	Entity * createMissile(double damage, double x, double y, double rotation, double linearSpeed);

private:
	Array<Entity *> entityStore;
};
#endif // !SCM_ENTITYFACTORY_H

