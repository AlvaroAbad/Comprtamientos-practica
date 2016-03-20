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

Image * ResourceStore::GetMenuButtonBackImage()
{
	if (!menuButtonBackNeutral) {
		menuButtonBackNeutral = ResourceManager::Instance().LoadImage(MENU_BUTTON_BACK_DIR);
	}
	return menuButtonBackNeutral;
}

Image * ResourceStore::GetMenuButtonBackPressedImage()
{
	if (!menuButtonBackPressed) {
		menuButtonBackPressed = ResourceManager::Instance().LoadImage(MENU_BUTTON_BACK_PRESSED_DIR);
	}
	return menuButtonBackPressed;
}

Image * ResourceStore::GetMenuButtonBackHooverImage()
{
	if (!menuButtonBackHoover) {
		menuButtonBackHoover = ResourceManager::Instance().LoadImage(MENU_BUTTON_BACK_HOOVER_DIR);
	}
	return menuButtonBackHoover;
}

Image * ResourceStore::GetAvatarImage()
{
	if (!avatar) {
		avatar = ResourceManager::Instance().LoadImage(AVATAR_DIR);
	}
	return avatar;
}

Image * ResourceStore::GetDreadnoughtImage()
{
	if (!dreadnought) {
		dreadnought = ResourceManager::Instance().LoadImage(DREADNOUGHT_DIR);
	}
	return dreadnought;
}

ResourceStore::~ResourceStore(){
}
