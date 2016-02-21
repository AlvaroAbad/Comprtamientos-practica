#ifndef UGINE_CONTROL_H
#define UGINE_CONTROL_H

#include "../../InputManager/include/event.h"
#include "../../Ugine/include/array.h"
#include "ieventlistener.h"
#include "../../InputManager/include/iregistrable.h"
#include "message.h"
class Control: public IRegistrable
{
public:
	virtual void OnEvent(const Event * action);
	void InjectMessage(const Message * message);
	virtual void Update()=0;
	virtual void Render()=0;
	virtual bool OnInputEvent(const Message * message)=0;
	void SetEventListener(IEventListener* eventListener) { this->eventListener = eventListener; }
	void AddChild(Control * child);
	Control();
	virtual ~Control();

protected:
	Control * father;
	Array<Control *> childs;
	IEventListener* eventListener;
	bool hasFocus;
};
#endif // !UGINE_CONROL_H

