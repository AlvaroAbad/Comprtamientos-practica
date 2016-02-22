#ifndef GUI_CLICKMESSAGE_H
#define GUI_CLICKMESSAGE_H

#include "message.h"
class ClickMessage : public Message
{
public:
	ClickMessage(float x, float y) : x(x), y(y) { SetType(MOUSE_BUTTON_CLICK); }
	~ClickMessage() {};
	float GetX() { return x; }
	float GetY() { return y; }
private:
	float x, y;
};
#endif // !GUI_CLICKMESSAGE_H
