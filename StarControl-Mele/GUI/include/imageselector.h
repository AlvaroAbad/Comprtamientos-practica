#ifndef GUI_IMAGESELECTOR_H
#define GUI_IMAGESELECTOR_H

#include "control.h"
#include "../../Ugine/include/image.h"

class ImageSelector : public Control
{
public:
	ImageSelector(String btnId,double imageWidth, double imageHeight, Image * Background=NULL) :Control(btnId),
		imageWidth(imageWidth), imageHeight(imageHeight),Background(Background) {
		selectedImage = -1;
		bool hasFocus = false;
	}

	virtual void Update();
	virtual void Render();
	virtual bool OnInputEvent(const Message * message);
	virtual void Register(inputs key, inputs action);
	virtual void Unregister(inputs key, inputs action);
	virtual void Unregister() {}
	virtual void AddImage(Image * item);
	virtual void SetDimensions(double width, double height) {
		Control::SetDimensions(width, height);
		maxColumns = width / imageWidth;
		maxRows = height / imageHeight;
	}

	~ImageSelector() {};

private:
	struct imageHolder {
		double posX, posY;
		Image * item;
	};
	Image * Background;
	Array<imageHolder> images;
	double imageWidth, imageHeight;
	float maxRows, maxColumns;
	int32 selectedImage;
};
#endif //!GUI_IMAGESELECTOR_H