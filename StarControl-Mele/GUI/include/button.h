#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include "control.h"
#include "../../Ugine/include/image.h"

class Button : public Control
{
public:
	Button(String btnId, Image * activeImage, Image * pressedImage = NULL, Image * hooverImage = NULL, Image * disabledImage = NULL) :Control(btnId),
		currentImage(activeImage), activeImage(activeImage), pressedImage(pressedImage), disabledImage(disabledImage), hooverImage(hooverImage) {
		bool hasFocus = false;
	}

	virtual void Update();
	virtual void Render();
	virtual bool OnInputEvent(const Message * message);
	virtual void Register(inputs key, inputs action);
	virtual void Unregister(inputs key, inputs action);
	virtual void Unregister() {}
	virtual void SetText(String text) {
		this->text = text;
	}
	
	~Button() {};

private:
	Image * currentImage;
	Image * activeImage;
	Image * pressedImage;
	Image * disabledImage;
	Image * hooverImage;
	String text;
};
#endif //!GUI_BUTTON_H
