#ifndef GUI_MOUSEBUTTONPRESSEDMESSAGE_H
#define GUI_MOUSEBUTTONPRESSEDMESSAGE_H

#include "message.h"
class MouseButtonPressedMessage : public Message
{
public:
	MouseButtonPressedMessage(float x, float y) : x(x), y(y) { SetType(MOUSE_BUTTON_PRESS); }
	~MouseButtonPressedMessage() {};
	float GetX()const { return x; }
	float GetY()const { return y; }
private:
	float x, y;
};
#endif // !GUI_MOUSEBUTTONPRESSEDMESSAGE_H
