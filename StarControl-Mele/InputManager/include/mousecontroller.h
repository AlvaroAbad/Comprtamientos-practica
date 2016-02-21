#ifndef UGINE_MOUSECONTROLLER_H
#define UGINE_MOUSECONTROLLER_H
class MouseController
{
public:
	MouseController() {};
	void Init();
	~MouseController() {}
	static void CursorPosition(int xpos, int ypos);
	static void MouseButtonEvent(int button, int action);
	static void MouseScrollEvent(int pos);
private:

};
#endif