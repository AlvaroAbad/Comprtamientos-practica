#ifndef INPUTMANAGER_KEYBORDCONTROLLER_H
#define INPUTMANAGER_KEYBORDCONTROLLER_H
class KeyBoardController
{
public:
	KeyBoardController() {};
	void Init();
	~KeyBoardController() {}
	static void KeyEvent(int button, int action);
private:

};
#endif // !INPUTMANAGER_KEYBORDCONTROLLER_H