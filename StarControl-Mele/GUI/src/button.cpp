#include "../../GUI/include/button.h"
#include "../../Ugine/include/renderer.h"
#include "../../GUI/include/mousebuttonpressedmessage.h"
#include "../../GUI/include/mousemovementmessage.h"
#include "../../Ugine/include/math.h"
#include "../../StarControl-Mele/include/resourcestore.h"
#include "../../Ugine/include/ttffont.h"
void Button::Update()
{
}

void Button::Render()
{
	if (isPositionRelative) {
		Renderer::Instance().DrawImage(currentImage, father->GetPositionX() + x, father->GetPositionY() + y, 0, width, height);
		ResourceStore::Instance().GetMainFont()->Render(text, father->GetPositionX() + x + 10, father->GetPositionY() + y + height / 2);
	}
	else {
		Renderer::Instance().DrawImage(currentImage, x, y, 0, width, height);
		ResourceStore::Instance().GetMainFont()->Render(text, x + 10, y + height /2);
	}
	
}

bool Button::OnInputEvent(const Message * message)
{
	double trueX, trueY;
	trueX = x;
	trueY = y;
	if (isPositionRelative) {
		trueX += father->GetPositionX();
		trueY += father->GetPositionY();
	}
	bool used = false;
	switch (message->GetType())
	{
	case Message::MOUSE_BUTTON_PRESS:
	{
		const MouseButtonPressedMessage * mousePressedButton = static_cast<const MouseButtonPressedMessage *>(message);
		if (PointInRect(mousePressedButton->GetX(), mousePressedButton->GetY(), trueX, trueY, width, height)) {
			currentImage = pressedImage;
			used = true;
			eventListener->OnClick(this);
		}
	}
	break;
	case Message::MOUSE_BUTTON_RELEASE:
		if (currentImage == pressedImage) {
			currentImage = hooverImage;
			used = true;
		}
		break;
	case Message::KEY_PRESS:
		if (hasFocus) {
			currentImage = pressedImage;
			used = true;
		}
		break;
	case Message::MOUSE_MOVE:
		const MouseMovementMessage * mouseMovement = static_cast<const MouseMovementMessage *>(message);
		if (PointInRect(mouseMovement->GetX(), mouseMovement->GetY(), trueX, trueY, width, height)) {
			currentImage = hooverImage;
		}
		else {
			currentImage = activeImage;
		}
		break;
	}
	return used;
}

void Button::Register(inputs key, inputs action)
{
	father->Register(key, action);
}

void Button::Unregister(inputs key, inputs action)
{
	father->Unregister(key, action);
}

