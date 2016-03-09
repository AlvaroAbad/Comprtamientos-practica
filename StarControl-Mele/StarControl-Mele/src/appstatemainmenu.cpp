#include "../include/appstatemainmenu.h"
#include "../../Ugine/include/resourcemanager.h"
#include "../../Ugine/include/string.h"
#include "../../GUI/include/menu.h"
#include "../../GUI/include/button.h"
#include "../../Ugine/include/screen.h"
#include "../../InputManager/include/eventmanager.h"
#include "../include/externs.h"
void AppStateMainMenu::run()
{
	window->Update();
}
void AppStateMainMenu::draw() const
{
	window->Render();
}
void AppStateMainMenu::getInputs()
{
	EventManager::Instance().DispachEvents();
}
void AppStateMainMenu::activate()
{
	uint16 width = Screen::Instance().GetWidth();
	uint16 height = Screen::Instance().GetHeight();
	String fileName = "../data/ui/mainmenubg.jpg";
	Image * background = ResourceManager::Instance().LoadImage(fileName);
	fileName = "../data/ui/mainmenu.png";
	Image * menuImg = ResourceManager::Instance().LoadImage(fileName);
	fileName = "../data/ui/mainmenubutton.png";
	Image * buttonImg = ResourceManager::Instance().LoadImage(fileName);
	fileName = "../data/ui/mainmenubuttonpressed.png";
	Image * buttonPressImg = ResourceManager::Instance().LoadImage(fileName);
	fileName = "../data/ui/mainmenubuttonhoover.png";
	Image * buttonHooverImg = ResourceManager::Instance().LoadImage(fileName);
	fileName = "../data/ui/mainmenubuttondisabled.png";
	Image * buttonDisabledImg = ResourceManager::Instance().LoadImage(fileName);

	window = new Window(background);
	window->SetPosition(0, 0);
	window->SetDimensions(width, height);

	Menu * menu = new Menu("mMain", menuImg);
	menu->setPositionType(true);
	menu->SetPosition(width / 2 - (menuImg->GetWidth() / 2), height / 2 - menuImg->GetHeight() / 2);
	menu->SetDimensions(menuImg->GetWidth(), menuImg->GetHeight());

	Button * buttonStart = new Button("btnStart", buttonImg, buttonPressImg, buttonHooverImg, buttonDisabledImg);
	buttonStart->setPositionType(true);
	buttonStart->SetPosition(10, 50);
	buttonStart->SetDimensions(menuImg->GetWidth() - 20, (menuImg->GetHeight() - 100) / 3);
	buttonStart->SetText("Start");
	menu->AddChild(buttonStart);

	Button * buttonOpc = new Button("btnOpt", buttonImg, buttonPressImg, buttonHooverImg, buttonDisabledImg);
	buttonOpc->setPositionType(true);
	buttonOpc->SetPosition(10, 60 + (menuImg->GetHeight() - 100) / 3);
	buttonOpc->SetDimensions(menuImg->GetWidth() - 20, (menuImg->GetHeight() - 100) / 3);
	buttonOpc->SetText("Options");
	menu->AddChild(buttonOpc);

	Button * buttonExit = new Button("btnExit", buttonImg, buttonPressImg, buttonHooverImg, buttonDisabledImg);
	buttonExit->setPositionType(true);
	buttonExit->SetPosition(10, 70 + ((menuImg->GetHeight() - 100) / 3) * 2);
	buttonExit->SetDimensions(menuImg->GetWidth() - 20, (menuImg->GetHeight() - 100) / 3);
	buttonExit->SetText("Exit");
	menu->AddChild(buttonExit);

	window->AddChild(menu);

	buttonStart->Register(inputs::MOUSE_BUTTON_LEFT, inputs::KEY_PRESS);
	buttonOpc->Register(inputs::MOUSE_BUTTON_LEFT, inputs::KEY_PRESS);
	buttonExit->Register(inputs::MOUSE_BUTTON_LEFT, inputs::KEY_PRESS);

	buttonStart->Register(inputs::MOUSE_BUTTON_LEFT, inputs::KEY_RELEASE);
	buttonOpc->Register(inputs::MOUSE_BUTTON_LEFT, inputs::KEY_RELEASE);
	buttonExit->Register(inputs::MOUSE_BUTTON_LEFT, inputs::KEY_RELEASE);

	buttonStart->Register(inputs::KEY_UNKNOWN, inputs::MOUSE_MOVEMENT);
	buttonOpc->Register(inputs::KEY_UNKNOWN, inputs::MOUSE_MOVEMENT);
	buttonExit->Register(inputs::KEY_UNKNOWN, inputs::MOUSE_MOVEMENT);

	buttonStart->SetEventListener(this);
	buttonOpc->SetEventListener(this);
	buttonExit->SetEventListener(this);
}

void AppStateMainMenu::deactivate()
{

}

void AppStateMainMenu::OnClick(Control * sender)
{
	if (*(sender->GetId()) == "btnExit") {
		whantedState = STATE_NULL;
	}else if (*(sender->GetId()) == "btnOpt") {
		whantedState = STATE_OPTIONS;
	}else if (*(sender->GetId()) == "btnStart") {
		whantedState = STATE_PREGAMEMENU;
	}
}
