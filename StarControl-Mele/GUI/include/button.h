#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include "control.h"
#include "../../Ugine/include/image.h"

class Button : public Control
{
public:
	virtual void Update();
	virtual void Render();
	virtual bool OnInputEvent(const Message * message);
	virtual void Register(inputs key, inputs action);
	virtual void Unregister(inputs key, inputs action);
	virtual void RegisterObserver(IEventListener * observer) {
		observers.Add(observer);
	}
	Button(String btnId,Image * activeImage, Image * pressedImage = NULL, Image * disabledImage = NULL, Image * hooverImage = NULL):Control(btnId),
		currentImage(activeImage), activeImage(activeImage), pressedImage(pressedImage), disabledImage(disabledImage), hooverImage(hooverImage) {

		bool hasFocus = false;
	}
	
	~Button() {};

private:
	Image * currentImage;
	Image * activeImage;
	Image * pressedImage;
	Image * disabledImage;
	Image * hooverImage;
	String text;
	Array<IEventListener *> observers;
};
#endif //!GUI_BUTTON_H
