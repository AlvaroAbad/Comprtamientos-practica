#ifndef SCM_MAINMENU_H
#define SCM_MAINMENU_H

#include "appState.h"
#include "../../GUI/include/window.h"
class AppStatePreGameMenu :public AppState, IEventListener
{
public:
	AppStatePreGameMenu() {
		this->setState(STATE_PREGAMEMENU);
		window = nullptr;
	};
	~AppStatePreGameMenu() { delete window; };
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
