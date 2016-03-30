#ifndef SCM_WEAPONCOMPONENTS_H
#define SCM_WEAPONCOMPONENTS_H

#include "subcomponent.h"
#include "componentmessages.h"

#pragma region SUBCOMPONENT_COOLDOWN
class SubComponentCooldown : public SubComponent {
public:
	SubComponentCooldown(float cooldown) :cooldown(cooldown), timeRemaing(cooldown){};
	virtual ~SubComponentCooldown() {};
	virtual void Update(float elapsed);
	virtual void ReciveMessage(Message * message);
private:
	float cooldown, timeRemaing;
}
#pragma endregion insert when the weapon has a cooldown

#pragma region SUBCOMPONENT_COST
class SubComponentCost : public SubComponent {
public:
	SubComponentCost(float cost) :cooldown(cooldown), timeRemaing(cooldown) {};
	virtual ~SubComponentCost() {};
	virtual void Update(float elapsed);
	virtual void ReciveMessage(Message * message);
private:
	float cooldown, timeRemaing;
}
#pragma endregion insert when the weapon has a cooldown
#endif // !SCM_WEAPONCOMPONENTS_H

