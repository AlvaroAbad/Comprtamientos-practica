#include "..\include\imageselector.h"
#include "../../Ugine/include/renderer.h"
#include "../../GUI/include/mousebuttonclickmessage.h"

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
		Renderer::Instance().DrawImage(images[i].item, father->GetPositionX() + images[i].posX, father->GetPositionY() + images[i].posY, 0, imageWidth, imageHeight);
	}
}

bool ImageSelector::OnInputEvent(const Message * message)
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
	case Message::MOUSE_BUTTON_CLICK:
	{
		const ClickMessage * mouseClick = static_cast<const ClickMessage *>(message);
		trueX = mouseClick->GetX() - father->GetPositionX();
		trueY = mouseClick->GetY() - father->GetPositionY();
		column = trueX / 50;
		row = trueY / 50;
		if (column < maxColumns && row<maxRows && row*column<images.Size()) {
			selectedImage = row*column;
		}
	}
	break;
	case Message::KEY_PRESS:
		//keyPressMessage
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
	images.Last().posX = images[images.Size() - 2].posX + imageWidth;
	images.Last().posY = images[images.Size() - 2].posY + imageHeight;
}
