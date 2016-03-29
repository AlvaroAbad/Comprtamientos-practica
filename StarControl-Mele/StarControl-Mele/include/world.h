#ifndef SCM_WORLD_H
#define SCM_WORLD_H

#include "../../Ugine/include/array.h"
#include "entityfactory.h"
#include "userinterface.h"

class Scene;
class Entity;
class EntityFactory;
class World
{
	friend void UserInterface::run();
public:
	World();
	void Init();// create selected entities
	void run();
	void draw();
	~World();

private:
	EntityFactory factory;
	Array<Entity *> entities;
	Entity * playerOne, *playerTwo;
};
#endif // !SCM_WORLD_H