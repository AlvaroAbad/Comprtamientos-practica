#ifndef UGINE_EVENT_H
#define UGINE_EVENT_H
#define TIME_TO_SETTLE 0.1f
#include "eventmanagerinputdefinitions.h"
class Event {
public:
	Event() {};
	Event(const inputs key, const inputs action, const int mousePosX,
		const int mousePosY, const int mouseScrollPosition)
		:key(key), action(action), mousePosX(mousePosX),
		mousePosY(mousePosY), mouseScrollPosition(mouseScrollPosition),
		TimeToSettle(TIME_TO_SETTLE){};
	~Event() {};
	void SetAction(const inputs action) { this->action = action; }
	void SetMousePos(const int mousePosX, const int mousePosY) {
		this->mousePosX = mousePosX;
		this->mousePosY = mousePosY;
	}
	void ReduceTimeToSettle(const float reduction) { TimeToSettle -= reduction;}
	void resetTimer() { TimeToSettle = TIME_TO_SETTLE; }
	inputs GetKey() const { return key; }
	inputs GetAction() const { return action; }
	int GetMousePosX() const { return mousePosX; }
	int GetMousePosY() const { return mousePosY; }
	int GetMouseScrollPosition() const { return mouseScrollPosition; }
	bool IsSettled() const { return TimeToSettle <= 0; }
	bool IsNew() const { return TimeToSettle == TIME_TO_SETTLE; }
	inline bool operator==(const Event& other) {
		return this->key == other.key && this->action == other.action;
	}
private:
	inputs key;
	inputs action;
	int mousePosX, mousePosY, mouseScrollPosition;
	float TimeToSettle;
};
#endif
