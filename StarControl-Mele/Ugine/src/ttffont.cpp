#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#include "..\include\ttffont.h"
#include "../include/stb_truetype.h"
#include <iostream>

using namespace std;

TTFFont::TTFFont(const String & filename, uint32 fontSize): fileName(filename), fontSize(fontSize), image(NULL)
{
	FILE* handle = fopen(filename.ToCString(), "rb");
	if (handle) {
		fseek(handle, 0, SEEK_END);
		long size = ftell(handle);
		fseek(handle, 0, SEEK_SET);
		uint8* buf = (uint8*)malloc(size);
		fread(buf, sizeof(uint8), size, handle);
		fclose(handle);

		stbtt_bakedchar charData[256];
		bool imgPacked = false;
		int imgsize = 32;
		uint8* alphaBuffer = NULL;
		while (!imgPacked) {
			alphaBuffer = (uint8*)malloc(imgsize * imgsize);
			if (stbtt_BakeFontBitmap(buf, 0, fontSize, alphaBuffer, imgsize, imgsize, 0, 256, charData) > 0) {
				imgPacked = true;
			}
			else {
				free(alphaBuffer);
				imgsize *= 2;
			}
		}
		free(buf);

		uint8* colorBuffer = (uint8*)malloc(imgsize * imgsize * 4);
		for (int i = 0; i < imgsize*imgsize; i++) {
			colorBuffer[i * 4 + 0] = alphaBuffer[i];
			colorBuffer[i * 4 + 1] = alphaBuffer[i];
			colorBuffer[i * 4 + 2] = alphaBuffer[i];
			colorBuffer[i * 4 + 3] = alphaBuffer[i];
		}
		free(alphaBuffer);

		image = new Image(colorBuffer, imgsize, imgsize);
		this->glyphs = new Array<Glyph>(256);
		for (unsigned int i = 0; i < 256; i++) {
			(*glyphs)[i].setHeight(charData[i].y1 - charData[i].y0);
			(*glyphs)[i].setWidth(charData[i].x1 - charData[i].x0);
			(*glyphs)[i].setX(charData[i].x0);
			(*glyphs)[i].setY(charData[i].y0);
			(*glyphs)[i].setOffsetY(charData[i].yoff);
		}
	}
}

TTFFont::~TTFFont()
{
	delete image;
	delete glyphs;
}

uint32 TTFFont::GetTextWidth(const String & text) const {
	uint32 textSize = 0;
	const char * chars = text.ToCString();
	for (uint32 i = 0; i < text.Length(); i++) {
		textSize += (*this->glyphs)[chars[i]].getWidth();
	}
	return textSize;
}

uint32 TTFFont::GetTextHeight(const String & text) const {
	const unsigned char * chars = (unsigned char *)text.ToCString();
	uint32 ret = 0;
	for (size_t i = 0; i < text.Length(); i++)
	{
		if ((*glyphs)[chars[i]].getHeight()>ret) {
			ret = (*glyphs)[chars[i]].getHeight();
		}
	}
	return ret;
}

void TTFFont::Render(const String & text, double x, double y) const {
	const unsigned char * chars = (unsigned char *)text.ToCString();
	uint32 textPosition = x;
	uint32 height= GetTextHeight(text);
	for (uint32 i = 0; i < text.Length(); i++) {
		double textY = y + (height + ((*this->glyphs)[chars[i]].getOffsetY()));
		Renderer::Instance().DrawImage(image, textPosition, textY, (*this->glyphs)[chars[i]].getX(), (*this->glyphs)[chars[i]].getY(), (*this->glyphs)[chars[i]].getWidth(), (*this->glyphs)[chars[i]].getHeight(), 0);
		textPosition += (*this->glyphs)[chars[i]].getWidth();
	}
}
