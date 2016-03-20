#include "..\include\appstatepregamemenu.h"
#include "../include/resourcestore.h"
#include "../../Ugine/include/screen.h"
#include "../../GUI/include/window.h"
#include "../../GUI/include/menu.h"
#include "../../GUI/include/button.h"
#include "../../GUI/include/imageselector.h"
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
	Image * avatarImg = ResourceStore::Instance().GetAvatarImage();
	Image * dreadnoughtImg = ResourceStore::Instance().GetDreadnoughtImage();

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

	window->AddChild(menu);

	Button * buttonBack = new Button("btnBack", buttonBackImg, buttonBackPressedImg, buttonBackHooverImg);
	buttonBack->setPositionType(true);
	buttonBack->SetPosition(10, 10);
	buttonBack->SetDimensions(buttonBackImg->GetWidth(), buttonImg->GetHeight());
	window->AddChild(buttonBack);

	ImageSelector * Player1ShipoSlector = new ImageSelector("iselPlayer1", 50, 50);
	Player1ShipoSlector->setPositionType(true);
	Player1ShipoSlector->SetPosition(0, buttonImg->GetHeight() + 20);
	Player1ShipoSlector->SetDimensions(width - menuImg->GetWidth(), height / 2, 10);
	Player1ShipoSlector->AddImage(avatarImg);
	Player1ShipoSlector->AddImage(dreadnoughtImg);
	window->AddChild(Player1ShipoSlector);
	

	buttonStart->Register(inputs::MOUSE_BUTTON_LEFT, inputs::KEY_PRESS);
	buttonBack->Register(inputs::MOUSE_BUTTON_LEFT, inputs::KEY_PRESS);

	buttonStart->Register(inputs::MOUSE_BUTTON_LEFT, inputs::KEY_RELEASE);
	buttonBack->Register(inputs::MOUSE_BUTTON_LEFT, inputs::KEY_RELEASE);

	buttonStart->Register(inputs::KEY_UNKNOWN, inputs::MOUSE_MOVEMENT);
	buttonBack->Register(inputs::KEY_UNKNOWN, inputs::MOUSE_MOVEMENT);

	Player1ShipoSlector->Register(inputs::MOUSE_BUTTON_LEFT, inputs::CLICK);
	Player1ShipoSlector->Register(inputs::KEY_LEFT, inputs::KEY_PRESS);
	Player1ShipoSlector->Register(inputs::KEY_RIGHT, inputs::KEY_PRESS);

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
