#include "..\include\menu.h"

void Menu::Update()
{
	for (int i = 0; i < childs.Size(); i++)
	{
		childs[i]->Update();
	}
}

void Menu::Render()
{
	if (image) {
		Renderer::Instance().SetBlendMode(Renderer::ALPHA);
		Renderer::Instance().DrawImage(image, x, y, 0, width, height);
	}
	for (int i = 0; i < childs.Size(); i++)
	{
		childs[i]->Render();
	}
}

bool Menu::OnInputEvent(const Message * message)
{
	bool used = false;
	uint32 i = 0;
	while (!used && i < this->childs.Size()) {
		used = this->childs[i]->OnInputEvent(message);
		i++;
	}
	return used;
}

void Menu::Register(inputs key, inputs action)
{
	father->Register(key, action);
}

void Menu::Unregister(inputs key, inputs action)
{
	father->Unregister(key, action);
}
