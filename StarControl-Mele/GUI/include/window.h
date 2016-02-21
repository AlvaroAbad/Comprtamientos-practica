#ifndef UGINE_WINDOW_H
#define UGINE_WINDOW_H
#include "control.h"
#include "../../Ugine/include/image.h"
class Window: public Control
{
public:
	virtual void Update();
	virtual void Render();
	virtual bool OnInputEvent(const Message * message);
	virtual void Register(inputs key, inputs action);
	virtual void Unregister(inputs key, inputs action);
	Window(Image * image) : image(image) {}
	~Window() {}

private:
	Image * image;
	double x, y;
	double width, height;
};
#endif // !UGINE_WINDOW_H

