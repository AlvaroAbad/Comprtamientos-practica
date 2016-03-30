#ifndef SCM_ENTITY_H
#define SCM_ENTITY_H

#include "../../Ugine/include/array.h"

class Message;
class Component;
class Entity
{
public:
	Entity(double x, double y, double width, double height, double rotation)
		: x(x),y(y),width(width), height(height), rotation(rotation) {};
	~Entity();
	void Update(float elapsed);
	void ReciveMessage(Message * message);
	void AddComponent(Component * component);

	/*Properties*/
	double x, y;
	double width, height;
	double rotation;
	bool dead;
private:
	Array<Component *> components;
};
#endif // !SCM_ENTITY_H
