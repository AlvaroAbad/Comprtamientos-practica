#include "..\include\appstatepregamemenu.h"
#include "../include/resourcestore.h"
#include "../../Ugine/include/screen.h"
#include "../../GUI/include/window.h"
#include "../../GUI/include/menu.h"
#include "../../GUI/include/button.h"
#include "../../InputManager/include/eventmanager.h"
#include "../include/externs.h"

void AppStatePreGameMenu::run()
{
	window->Update();
}

void AppStatePreGameMenu::draw() const
{
	window->Render();
}

void AppStatePreGameMenu::getInputs()
{
	EventManager::Instance().DispachEvents();
}

void AppStatePreGameMenu::activate()
{
	uint16 width = Screen::Instance().GetWidth();
	uint16 height = Screen::Instance().GetHeight();
	Image * background = ResourceStore::Instance().GetMenuBackGround();
	Image * menuImg = ResourceStore::Instance().GetMenuImage();
	Image * buttonImg = ResourceStore::Instance().GetMenuButtonNeutralImage();
	Image * buttonPressImg = ResourceStore::Instance().GetMenuButtonPressedImage();
	Image * buttonHooverImg = ResourceStore::Instance().GetMenuButtonHooverImage();
	Image * buttonDisabledImg = ResourceStore::Instance().GetMenuButtonDisabledImage();
	Image * buttonBackImg = ResourceStore::Instance().GetMenuButtonBackImage();
	Image * buttonBackPressedImg = ResourceStore::Instance().GetMenuButtonBackPressedImage();
	Image * buttonBackHooverImg = ResourceStore::Instance().GetMenuButtonBackHooverImage();

	/*Create Window*/
	window = new Window(background);
	window->SetPosition(0, 0);
	window->SetDimensions(width, height);

	/*Create Menu Holder*/
	Menu * menu = new Menu("mMain", menuImg);
	menu->setPositionType(true);
	menu->SetPosition(width - menuImg->GetWidth(),0);
	menu->SetDimensions(menuImg->GetWidth(), height);

	/*Crete Menu Buttons*/
	Button * buttonStart = new Button("btnStart", buttonImg, buttonPressImg, buttonHooverImg, buttonDisabledImg);
	buttonStart->setPositionType(true);
	buttonStart->SetPosition(10, height- buttonImg->GetHeight()-10);
	buttonStart->SetDimensions(menu->GetWidth()-60, buttonImg->GetHeight());
	buttonStart->SetText("Start");
	menu->AddChild(buttonStart);

	Button * buttonBack = new Button("btnBack", buttonBackImg, buttonBackPressedImg, buttonBackHooverImg);
	buttonBack->setPositionType(true);
	buttonBack->SetPosition(10, 10);
	buttonBack->SetDimensions(buttonBackImg->GetWidth(), buttonImg->GetHeight());
	window->AddChild(buttonBack);

	window->AddChild(menu);

	buttonStart->Register(inputs::MOUSE_BUTTON_LEFT, inputs::KEY_PRESS);
	buttonBack->Register(inputs::MOUSE_BUTTON_LEFT, inputs::KEY_PRESS);

	buttonStart->Register(inputs::MOUSE_BUTTON_LEFT, inputs::KEY_RELEASE);
	buttonBack->Register(inputs::MOUSE_BUTTON_LEFT, inputs::KEY_RELEASE);

	buttonStart->Register(inputs::KEY_UNKNOWN, inputs::MOUSE_MOVEMENT);
	buttonBack->Register(inputs::KEY_UNKNOWN, inputs::MOUSE_MOVEMENT);

	buttonBack->SetEventListener(this);
}

void AppStatePreGameMenu::deactivate()
{
	window->Unregister();
}

void AppStatePreGameMenu::OnClick(Control * sender)
{

	if (*(sender->GetId()) == "btnBack") {
		whantedState = STATE_MAINMENU;
	}
}
