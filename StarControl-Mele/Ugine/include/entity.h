#ifndef UGINE_ENTITY_H
#define UGINE_ENTITY_H
#include "InputManager\iregistrable.h"
#include "sprite.h"
class Entity : public IRegistrable
{
public:
	Entity(Image * image);
	void Register(inputs key, inputs action);
	void Unregister(inputs key, inputs action);
	~Entity() {};
	void setPosition(int x, int y) { body->SetPosition(x, y); }
	virtual void OnEvent(const Event * action);
	void render() { body->Render(); }
private:
	Sprite * body;
	int mousePosX, mousePosY;
};
#endif
