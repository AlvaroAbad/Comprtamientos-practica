#include "..\include\weaponscomponents.h"
#include "../include/component.h"
#pragma region SUBCOMPONENT_COOLDOWN
void SubComponentCooldown::Update(float elapsed)
{
	if (timeRemaing > 0) {
		timeRemaing -= elapsed;
		if (timeRemaing <= 0) {
			MessageSetWaponReady msgWReady;
			father->ReciveMessage(&msgWReady);
		}
	}
}

void SubComponentCooldown::ReciveMessage(Message * message)
{
	if (message->type == Message::MSG_FIRE) {
		timeRemaing = cooldown;
	}
}
#pragma endregion insert when the weapon has a cooldown