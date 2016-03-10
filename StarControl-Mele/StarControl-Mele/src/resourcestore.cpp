#include "..\include\resourcestore.h"
#include "../../Ugine/include/resourcemanager.h"
ResourceStore* ResourceStore::store = nullptr;

ResourceStore & ResourceStore::Instance(){
	if (!store)
		store = new ResourceStore();
	return *store;
}

TTFFont * ResourceStore::GetMainFont(){
	if (!mainFont) {
		mainFont = ResourceManager::Instance().LoadTTFFont(MAIN_FONT_DIR, 30);
	}
	return mainFont;
}

Image * ResourceStore::GetMenuBackGround()
{
	if (!menuBackGround) {
		menuBackGround = ResourceManager::Instance().LoadImage(MENU_BACKGROUND_DIR);
	}
	return menuBackGround;
}

Image * ResourceStore::GetMenuImage()
{
	if (!menuImage) {
		menuImage = ResourceManager::Instance().LoadImage(MENU_IMAGE_DIR);
	}
	return menuImage;
}

Image * ResourceStore::GetMenuButtonNeutralImage()
{
	if (!menuButtonNeutral) {
		menuButtonNeutral = ResourceManager::Instance().LoadImage(MENU_BUTTON_NEUTRAL_DIR);
	}
	return menuButtonNeutral;
}

Image * ResourceStore::GetMenuButtonPressedImage()
{
	if (!menuButtonPressed) {
		menuButtonPressed = ResourceManager::Instance().LoadImage(MENU_BUTTON_PRESSED_DIR);
	}
	return menuButtonPressed;
}

Image * ResourceStore::GetMenuButtonHooverImage()
{
	if (!menuButtonHoover) {
		menuButtonHoover = ResourceManager::Instance().LoadImage(MENU_BUTTON_HOOVER_DIR);
	}
	return menuButtonHoover;
}

Image * ResourceStore::GetMenuButtonDisabledImage()
{
	if (!menuButtonDisabled) {
		menuButtonDisabled = ResourceManager::Instance().LoadImage(MENU_BUTTON_DISABLED_DIR);
	}
	return menuButtonDisabled;
}

ResourceStore::~ResourceStore(){
}
