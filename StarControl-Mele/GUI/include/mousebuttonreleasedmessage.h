#ifndef GUI_MOUSEBUTTONRELEASSEDMESSAGE_H
#define GUI_MOUSEBUTTONRELEASSEDMESSAGE_H

#include "message.h"
class MouseButtonReleassedMessage : public Message
{
public:
	MouseButtonReleassedMessage(float x, float y) : x(x), y(y) { SetType(MOUSE_BUTTON_RELEASE); }
	~MouseButtonReleassedMessage() {};
	float GetX()const { return x; }
	float GetY()const { return y; }
private:
	float x, y;
};
#endif // !GUI_MOUSEBUTTONRELEASSEDMESSAGE_H
