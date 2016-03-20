#ifndef GUI_IMAGESELECTOR_H
#define GUI_IMAGESELECTOR_H

#include "control.h"
#include "../../Ugine/include/image.h"

class ImageSelector : public Control
{
public:
	ImageSelector(String btnId, double imageWidth, double imageHeight, Image * Background = nullptr) :Control(btnId),
		imageWidth(imageWidth), imageHeight(imageHeight), Background(Background) {
		selectedImage = -1;
		bool hasFocus = false;
	}

	virtual void Update();
	virtual void Render();
	virtual bool OnInputEvent(const GUIMessage * message);
	virtual void Register(inputs key, inputs action);
	virtual void Unregister(inputs key, inputs action);
	virtual void Unregister() {}
	virtual void AddImage(Image * item);
	virtual void SetDimensions(double width, double height, double margin) {
		Control::SetDimensions(width, height);
		this->margin = margin;
		maxColumns = width / (imageWidth + (2 * margin));
		maxRows = height / (imageHeight + (2 * margin));
	}

	~ImageSelector() {};

private:
	struct imageHolder {
		double posX, posY;
		Image * item;
	};
	Image * Background;
	Array<imageHolder> images;
	double imageWidth, imageHeight, margin;
	uint32 maxRows, maxColumns;
	int32 selectedImage;
};
#endif //!GUI_IMAGESELECTOR_H