#ifndef UGINE_DRAGMESSAGE_H
#define UGINE_DRAGMESSAGE_H

#include "message.h"
class DragMessage : public Message
{
public:
	DragMessage(float x, float y) : x(x), y(y) { SetType(DRAG); }
	~DragMessage() {};
	float GetX() { return x; }
	float GetY() { return y; }
private:
	float x, y;
};
#endif // !UGINE_DRAGMESSAGE_H