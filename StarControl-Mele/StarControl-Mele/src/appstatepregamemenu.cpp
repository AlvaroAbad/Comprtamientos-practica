#include "..\include\appstatepregamemenu.h"
#include "../include/resourcestore.h"
#include "../../Ugine/include/screen.h"
#include "../../GUI/include/window.h"
#include "../../GUI/include/menu.h"
#include "../../GUI/include/button.h"
#include "../../InputManager/include/eventmanager.h"

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
	buttonStart->SetDimensions(buttonImg->GetWidth(), buttonImg->GetHeight());
	buttonStart->SetText("Start");
	menu->AddChild(buttonStart);

	window->AddChild(menu);
}

void AppStatePreGameMenu::deactivate()
{
}

void AppStatePreGameMenu::OnClick(Control * sender)
{
}
