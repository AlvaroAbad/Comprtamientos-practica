#ifndef SCM_RESOURCESSTORE_H
#define SCM_RESOURCESSTORE_H
class TTFFont;
class Image;
class ResourceManager;
class ResoruceStore {
public:
	static	ResoruceStore& Instance();
	TTFFont* GetMainFont();
protected:
	ResoruceStore() {}
	virtual ~ResoruceStore();
private:
	static ResoruceStore* store;
	TTFFont * mainFont;

#define MAIN_FONT_DIR "../data/Fonts/spaceage.ttf"
};
#endif // !SCM_RESOURCESSTORE_H

