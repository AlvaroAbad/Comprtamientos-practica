#ifndef UGINE_MOUSEMOVEMENTMESSAGE_H
#define UGINE_MOUSEMOVEMENTMESSAGE_H

#include "message.h"
class MouseMovementMessage: public Message
{
public:
	MouseMovementMessage(float x, float y): x(x), y(y){ SetType(MOUSE_MOVE); }
	~MouseMovementMessage() {};
	float GetX() const { return x; }
	float GetY()const { return y; }
private:
	float x, y;
};

#endif // !UGINE_MOUSEMOVEMENTMESSAGE_H
