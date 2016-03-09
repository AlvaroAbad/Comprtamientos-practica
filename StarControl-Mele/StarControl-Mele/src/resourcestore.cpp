#include "..\include\resourcestore.h"
#include "../../Ugine/include/resourcemanager.h"
ResoruceStore* ResoruceStore::store = nullptr;

ResoruceStore & ResoruceStore::Instance(){
	if (!store)
		store = new ResoruceStore();
	return *store;
}

TTFFont * ResoruceStore::GetMainFont(){
	if (!mainFont) {
		mainFont = ResourceManager::Instance().LoadTTFFont(MAIN_FONT_DIR, 30);
	}
	return mainFont;
}

ResoruceStore::~ResoruceStore(){
}
