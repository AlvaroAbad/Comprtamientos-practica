#ifndef UGINE_BUTTON_H
#define UGINE_BUTTON_H

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
	Button(Image * activeImage, Image * pressedImage = NULL, Image * disabledImage = NULL, Image * hooverImage = NULL)
		:currentImage(activeImage), activeImage(activeImage), pressedImage(pressedImage), disabledImage(disabledImage), hooverImage(hooverImage) {
		
		bool hasFocus = false;
	}
	void SetPosition(double x, double y) {
		this->x = x;
		this->y = y;
	}
	void SetDimensions(double width, double height) {
		this->width = width;
		this->height = height;
	}
	~Button() {};

private:
	Image * currentImage;
	Image * activeImage;
	Image * pressedImage;
	Image * disabledImage;
	Image * hooverImage;
	bool hasFocus;
	double x, y;
	double width, height;
	String text;
};
#endif //!UGINE_BUTTON_H
