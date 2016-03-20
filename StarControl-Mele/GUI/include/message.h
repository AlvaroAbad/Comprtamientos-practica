#ifndef GUI_MESSAGE_H
#define GUI_MESSAGE_H

class GUIMessage
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
	enum KeyCode {
		KEY_SPECIAL = 256,
		KEY_UP = (KEY_SPECIAL + 27),
		KEY_DOWN = (KEY_SPECIAL + 28),
		KEY_LEFT = (KEY_SPECIAL + 29),
		KEY_RIGHT = (KEY_SPECIAL + 30),
	};
	GUIMessage() {};
	virtual ~GUIMessage() {};
	void SetType(MessageType type) { this->type = type; }
	MessageType GetType() const  { return type; }
private:
	MessageType type;
};

class ClickMessage : public GUIMessage
{
public:
	ClickMessage(float x, float y) : x(x), y(y) { SetType(MOUSE_BUTTON_CLICK); }
	~ClickMessage() {};
	float GetX() const { return x; }
	float GetY() const { return y; }
private:
	float  x, y;
};

class MouseButtonPressedMessage : public GUIMessage
{
public:
	MouseButtonPressedMessage(float x, float y) : x(x), y(y) { SetType(MOUSE_BUTTON_PRESS); }
	~MouseButtonPressedMessage() {};
	float GetX()const { return x; }
	float GetY()const { return y; }
private:
	float x, y;
};

class MouseButtonReleassedMessage : public GUIMessage
{
public:
	MouseButtonReleassedMessage(float x, float y) : x(x), y(y) { SetType(MOUSE_BUTTON_RELEASE); }
	~MouseButtonReleassedMessage() {};
	float GetX()const { return x; }
	float GetY()const { return y; }
private:
	float x, y;
};

class MouseMovementMessage : public GUIMessage
{
public:
	MouseMovementMessage(float x, float y) : x(x), y(y) { SetType(MOUSE_MOVE); }
	~MouseMovementMessage() {};
	float GetX() const { return x; }
	float GetY()const { return y; }
private:
	float x, y;
};

class DragMessage : public GUIMessage
{
public:
	DragMessage(float x, float y) : x(x), y(y) { SetType(DRAG); }
	~DragMessage() {};
	float GetX()const { return x; }
	float GetY()const { return y; }
private:
	float x, y;
};

class KeyPressedMessage : public GUIMessage
{
public:
	KeyPressedMessage(KeyCode key) : key(key){ SetType(KEY_PRESS); }
	~KeyPressedMessage() {};
	float GetKey()const { return key; }
private:
	KeyCode key;
};
#endif // !GUI_MESSAGE_H
