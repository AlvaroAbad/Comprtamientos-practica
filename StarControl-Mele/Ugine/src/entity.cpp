#include "../include/entity.h"
#include "../include/InputManager/managergameinterface.h"
Entity::Entity(Image * image)
{
	body = new Sprite(image);
}

void Entity::Register(inputs key, inputs action)
{
	ManagerGameInterface::Register(this, key, action);
}

void Entity::Unregister(inputs key, inputs action)
{
	ManagerGameInterface::Unregister(this, key, action);
}

void Entity::OnEvent(const Event * action)
{
	switch (action->GetAction())
	{
	case MOUSE_MOVEMENT:
		this->mousePosX = action->GetMousePosX();
		this->mousePosY = action->GetMousePosY();
		break;
	case KEY_PRESSED_DOWN:
		if (action->GetKey() == inputs::MOUSE_BUTTON_LEFT) {
			body->SetPosition(this->mousePosX, this->mousePosY);
		}
		else if (action->GetKey() == inputs::MOUSE_BUTTON_RIGHT) {
			body->SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
		}
		else if (action->GetKey() == inputs::KEY_SPACE) {
			body->SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
		}
	default:
		break;
	}
}
