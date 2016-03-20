#ifndef SCM_RESOURCESSTORE_H
#define SCM_RESOURCESSTORE_H
class TTFFont;
class Image;
class ResourceManager;
class ResourceStore {
public:
	static	ResourceStore& Instance();
	TTFFont* GetMainFont();
	Image * GetMenuBackGround();
	Image * GetMenuImage();
	Image * GetMenuButtonNeutralImage();
	Image * GetMenuButtonPressedImage();
	Image * GetMenuButtonHooverImage();
	Image * GetMenuButtonDisabledImage();
	Image * GetMenuButtonBackImage();
	Image * GetMenuButtonBackPressedImage();
	Image * GetMenuButtonBackHooverImage();
	Image * GetAvatarImage();
	Image * GetDreadnoughtImage();
protected:
	ResourceStore() {
		mainFont = nullptr;
		menuBackGround = nullptr;
	}
	virtual ~ResourceStore();
private:
	static ResourceStore* store;
	TTFFont * mainFont;
	Image * menuBackGround;
	Image * menuImage;
	Image * menuButtonNeutral;
	Image * menuButtonPressed;
	Image * menuButtonHoover;
	Image * menuButtonDisabled;
	Image * menuButtonBackNeutral;
	Image * menuButtonBackPressed;
	Image * menuButtonBackHoover;
	Image * avatar;
	Image * dreadnought;

#define MAIN_FONT_DIR "../data/Fonts/spaceage.ttf"
#define MENU_BACKGROUND_DIR "../data/ui/mainmenubg.jpg"
#define MENU_IMAGE_DIR "../data/ui/mainmenu.png"
#define MENU_BUTTON_NEUTRAL_DIR "../data/ui/mainmenubutton.png"
#define MENU_BUTTON_PRESSED_DIR "../data/ui/mainmenubuttonpressed.png"
#define MENU_BUTTON_HOOVER_DIR "../data/ui/mainmenubuttonhoover.png"
#define MENU_BUTTON_DISABLED_DIR "../data/ui/mainmenubuttondisabled.png"
#define MENU_BUTTON_BACK_DIR "../data/ui/back.png"
#define MENU_BUTTON_BACK_PRESSED_DIR "../data/ui/backpressed.png"
#define MENU_BUTTON_BACK_HOOVER_DIR "../data/ui/backhoover.png"

#define AVATAR_DIR "../data/sc2/ChmmrAvatar/avatar.png"
#define DREADNOUGHT_DIR "../data/sc1/KzerZaDreadnought/dreadnought.png"
};
#endif // !SCM_RESOURCESSTORE_H

