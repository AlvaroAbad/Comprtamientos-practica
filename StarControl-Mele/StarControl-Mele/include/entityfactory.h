#ifndef SCM_ENTITYFACTORY_H
#define SCM_ENTITYFACTORY_H

#include "../../Ugine/include/array.h"

class Entity;
class EntityFactory
{
public:
	EntityFactory() {};
	~EntityFactory() {};
	Entity * CreatePlayerOne();
	Entity * CreatePlayerTwo();
	Entity * CreateDrone(double x, double y, double rotation);
	Entity * CreateShipExplosion(double x, double y);

private:
	Array<Entity *> entityStore;
};
#endif // !SCM_ENTITYFACTORY_H

