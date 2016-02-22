#include "../../GUI/include/button.h"
#include "../../Ugine/include/renderer.h"
#include "../../GUI/include/mousebuttonpressedmessage.h"
#include "../../GUI/include/mousemovementmessage.h"
#include "../../Ugine/include/math.h"
void Button::Update()
{
}

void Button::Render()
{
	Renderer::Instance().DrawImage(currentImage, x, y, 0, width, height);
}

bool Button::OnInputEvent(const Message * message)
{
	bool used = false;
	switch (message->GetType())
	{
	case Message::MOUSE_BUTTON_PRESS:
	{
		const MouseButtonPressedMessage * mousePressedButton = static_cast<const MouseButtonPressedMessage *>(message);
		if (PointInRect(mousePressedButton->GetX(), mousePressedButton->GetY(), x, y, width, height)) {
			currentImage = pressedImage;
			used = true;
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
		if (PointInRect(mouseMovement->GetX(), mouseMovement->GetY(), x, y, width, height)) {
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

