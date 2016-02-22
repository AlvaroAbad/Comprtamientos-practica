#ifndef SCM_MAINMENU_H
#define SCM_MAINMENU_H

#include "appState.h"
#include "../../GUI/include/window.h"
class AppStateMainMenu:public AppState, IEventListener
{
public:
	AppStateMainMenu() {
		this->setState(STATE_MENU);
		window = nullptr;
	};
	~AppStateMainMenu() { delete window; };
	void virtual run();
	void virtual draw() const;
	void virtual getInputs();
	void virtual activate();
	void virtual deactivate();
	void OnClick(Control * sender);
private:
	Window * window;
};

#endif // !SCM_MAINMENU_H

