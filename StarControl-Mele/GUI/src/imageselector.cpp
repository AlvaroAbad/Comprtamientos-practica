#include "..\include\imageselector.h"
#include "../../Ugine/include/renderer.h"
#include "../../GUI/include/message.h"

void ImageSelector::Update()
{
}

void ImageSelector::Render()
{
	if (Background) {
		if (isPositionRelative) {
			Renderer::Instance().DrawImage(Background, father->GetPositionX() + x, father->GetPositionY() + y, 0, width, height);
		}
		else {
			Renderer::Instance().DrawImage(Background, x, y, 0, width, height);
		}
	}
	for (uint32 i = 0; i < images.Size(); i++)
	{
		if (selectedImage == i) {
			Renderer::Instance().SetColor(255, 255, 255, 255);
			Renderer::Instance().DrawRect(father->GetPositionX() + images[i].posX - margin, father->GetPositionY() + images[i].posY - margin, imageWidth + margin * 2, imageHeight + margin * 2);
		}
		Renderer::Instance().DrawImage(images[i].item, father->GetPositionX() + images[i].posX, father->GetPositionY() + images[i].posY, 0, imageWidth, imageHeight);
	}
}

bool ImageSelector::OnInputEvent(const GUIMessage * message)
{
	double trueX, trueY;
	uint32 row, column;
	trueX = x;
	trueY = y;
	if (isPositionRelative) {
		trueX += father->GetPositionX();
		trueY += father->GetPositionY();
	}
	bool used = false;
	switch (message->GetType())
	{
	case GUIMessage::MOUSE_BUTTON_CLICK:
	{
		const ClickMessage * mouseClick = static_cast<const ClickMessage *>(message);
		trueX = mouseClick->GetX() - father->GetPositionX();
		trueY = mouseClick->GetY() - father->GetPositionY();
		column = trueX / 50;
		row = trueY / 50;
		if (column < maxColumns && row < maxRows && row*column < images.Size()) {
			selectedImage = row*column;
			used = true;
		}
	}
	break;
	case GUIMessage::KEY_PRESS:
		const KeyPressedMessage * keyPressed = static_cast<const KeyPressedMessage *>(message);
		if (keyPressed->GetKey() == GUIMessage::KEY_LEFT) {
			selectedImage--;
			used = true;
		}
		else if (keyPressed->GetKey() == GUIMessage::KEY_RIGHT) {
			selectedImage++;
			used = true;
		}
	}
	return used;
}

void ImageSelector::Register(inputs key, inputs action)
{
}

void ImageSelector::Unregister(inputs key, inputs action)
{
}

void ImageSelector::AddImage(Image * item)
{
	images.Add(imageHolder());
	images.Last().item = item;
	if (images.Size() > 1) {
		if (images.Size() % maxColumns) {
			images.Last().posX = margin;
			images.Last().posY = images[images.Size() - 2].posY + imageHeight + margin;
		}
		else {
			images.Last().posX = images[images.Size() - 2].posX + imageWidth + margin;
			images.Last().posY = images[images.Size() - 2].posY + imageHeight;
		}
	}
	else {
		images.Last().posX = margin;
		images.Last().posY = margin;
	}

}
