#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "../include/u-gine.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "../include/entity.h"


int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);
	String fileName;
	MouseController mc;
	KeyBoardController kc;
	mc.Init();
	kc.Init();
/*
	String *FileName = new String();
	*FileName = "../data/star.png";
	Image * star = ResourceManager::Instance().LoadImage(*FileName);
	star->SetMidHandle();
	Entity *player = new Entity(star);
	player->Register(inputs::MOUSE_BUTTON_LEFT, inputs::KEY_PRESSED_DOWN);
	player->Register(inputs::MOUSE_BUTTON_RIGHT, inputs::KEY_PRESSED_DOWN);
	player->Register(inputs::KEY_SPACE, inputs::KEY_PRESSED_DOWN);
	player->Register(inputs::KEY_UNKNOWN, inputs::MOUSE_MOVEMENT);
	player->setPosition(10, 10);
	*/
	Window * window = new Window(NULL);

	fileName = "../data/button.png";
	Image * buttonImg= ResourceManager::Instance().LoadImage(fileName);
	fileName = "../data/buttonHoover.png";
	Image * hooverImg = ResourceManager::Instance().LoadImage(fileName);
	fileName = "../data/buttonActive.png";
	Image * activeImg = ResourceManager::Instance().LoadImage(fileName);

	Button * button = new Button(buttonImg, activeImg, NULL, hooverImg);
	button->SetPosition(10, 10);
	button->SetDimensions(50, 20);
	window->AddChild(button);
	button->Register(inputs::MOUSE_BUTTON_LEFT, inputs::KEY_PRESS);
	button->Register(inputs::MOUSE_BUTTON_LEFT, inputs::KEY_RELEASE);
	button->Register(inputs::KEY_UNKNOWN, inputs::MOUSE_MOVEMENT);

	while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		window->Update();
		window->Render();
		// Refrescamos la pantalla
		EventManager::Instance().DispachEvents();
		Screen::Instance().Refresh();
		Renderer::Instance().Clear(0, 0, 0);
	}
	
	Screen::Instance().Close();
	ResourceManager::Instance().FreeResources();
	return 0;
}
