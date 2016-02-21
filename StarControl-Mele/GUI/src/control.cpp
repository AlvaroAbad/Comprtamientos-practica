#include "../../GUI/include/control.h"
#include "../../GUI/include/mousemovementmessage.h"
#include "../../GUI/include/dragmessage.h"
#include "../../GUI/include/mousebuttonclickmessage.h"
#include "../../GUI/include/mousebuttonpressedmessage.h"
#include "../../GUI/include/mousebuttonreleasedmessage.h"
#pragma warning (disable : 4062 ) 
void Control::OnEvent(const Event * action)
{
	Message * message=nullptr;
	switch (action->GetAction())
	{
	case KEY_RELEASE:
		if (action->GetKey() <= inputs::MOUSE_BUTTON_LAST) {
			message = new MouseButtonReleassedMessage(action->GetMousePosX(), action->GetMousePosY());
		}
		else {
			//KeyReleaseMessage
		}
		break;
	case KEY_PRESS:
		if (action->GetKey() <= inputs::MOUSE_BUTTON_LAST) {
			message = new MouseButtonPressedMessage(action->GetMousePosX(), action->GetMousePosY());
		}
		else {
			//KeyPressMessage
		}
		break;
	case CLICK:
		message = new ClickMessage(action->GetMousePosX(), action->GetMousePosY());
		break;
	case DOUBLE_CLICK:
		//mouseNuttonDoubleClickMessage
		break;
	case DRAG:
		message = new DragMessage(action->GetMousePosX(), action->GetMousePosY());
		break;
	case SCROLL_UP:
		//mouseScrollUpMessage
		break;
	case SCROLL_DOWN:
		//mouseScrollDownMessage
		break;
	case MOUSE_MOVEMENT:
		message = new MouseMovementMessage(action->GetMousePosX(), action->GetMousePosY());
		break;
	}
	InjectMessage(message);
	delete message;
}

void Control::InjectMessage(const Message * message)
{
	OnInputEvent(message);
}

void Control::AddChild(Control * child)
{
	child->father = this;
	childs.Add(child);
}

Control::Control()
{
}

Control::~Control()
{
}
