#ifndef UGINE_KEYBORDCONTROLLER_H
#define UGINE_KEYBORDCONTROLLER_H
class KeyBoardController
{
public:
	KeyBoardController() {};
	void Init();
	~KeyBoardController() {}
	static void KeyEvent(int button, int action);
private:

};
#endif