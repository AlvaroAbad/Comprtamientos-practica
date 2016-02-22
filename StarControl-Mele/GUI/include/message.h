#ifndef GUI_MESSAGE_H
#define GUI_MESSAGE_H

class Message
{
public:
	enum MessageType {
		MOUSE_BUTTON_RELEASE,
		MOUSE_BUTTON_PRESS,
		KEY_RELEASE,
		KEY_PRESS,
		MOUSE_BUTTON_CLICK,
		MOUSE_BUTTON_DOUBLECLICK,
		DRAG,
		SCROLL,
		MOUSE_MOVE
	};
	Message() {};
	virtual ~Message() {};
	void SetType(MessageType type) { this->type = type; }
	MessageType GetType() const  { return type; }
private:
	MessageType type;
};

#endif // !GUI_MESSAGE_H
