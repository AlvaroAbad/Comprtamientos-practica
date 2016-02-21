#ifndef UGINE_REGISTRABLE_H
#define UGINE_REGISTRABLE_H
#include "eventmanagerinputdefinitions.h"
#include "event.h"
class IRegistrable
{
public:
	virtual void Register(inputs key, inputs action)=0;
	virtual void Unregister(inputs key, inputs action)=0;
	virtual void OnEvent(const Event *action) = 0;
};
#endif