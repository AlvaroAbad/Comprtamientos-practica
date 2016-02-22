#ifndef GUI_MENU_H
#define GUI_MENU_H
#include "control.h"
#include "../../Ugine/include/image.h"
class Menu : public Control
{
public:
	virtual void Update();
	virtual void Render();
	virtual bool OnInputEvent(const Message * message);
	virtual void Register(inputs key, inputs action);
	virtual void Unregister(inputs key, inputs action);
	void SetPosition(double x, double y) {
		this->x = x;
		this->y = y;
	}
	double GetPositionX() { return x; }
	double GetPositionY() { return y; }
	void SetDimensions(double width, double height) {
		this->width = width;
		this->height = height;
	}
	Menu(Image * image) : image(image) {}
	~Menu() {}

private:
	Image * image;
	double x, y;
	double width, height;
};
#endif // !GUI_MENU_H
