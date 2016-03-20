#include "../../GUI/include/window.h"
#include "../../Ugine/include/renderer.h"
#include "../../InputManager/include/managergameinterface.h"
void Window::Update()
{
	for (int i = 0; i < childs.Size(); i++)
	{
		childs[i]->Update();
	}
}

void Window::Render()
{
	if (image) {
		Renderer::Instance().SetBlendMode(Renderer::SOLID);
		Renderer::Instance().DrawImage(image, x, y, 0, width, height);
	}
	for (int i = 0; i < childs.Size(); i++)
	{
		childs[i]->Render();
	}
}

bool Window::OnInputEvent(const GUIMessage * message)
{
	bool used = false;
	uint32 i = 0;
	while (!used && i < this->childs.Size()) {
		used = this->childs[i]->OnInputEvent(message);
		i++;
	}
	return used;
}

void Window::Register(inputs key, inputs action)
{
	ManagerGameInterface::Register(this, key, action);
}

void Window::Unregister(inputs key, inputs action)
{
	ManagerGameInterface::Unregister(this, key, action);
}

void Window::Unregister()
{
	ManagerGameInterface::UnregisterAll(this);
}

Window::~Window()
{
	for (uint32 i = 0; i < childs.Size(); i++)
	{
		delete childs[i];
	}
}
