#pragma once
#include "Definitions.h"

class Iteminfo {
public:
	Iteminfo(item itemid, TextureID itemtexture=0) :id(itemid), texture(itemtexture) {}
	item id;
	TextureID texture;
};

enum BuiltInItems {
	STICK = 30000, APPLE
};

extern Iteminfo itemsinfo[];
const item theFirstItem = STICK;

void loadItemsTextures();

inline bool isBlock(item i) {
	return i < theFirstItem;
}

inline TextureID getItemTexture(item i){
	if (isBlock(i)) return BlockTextures;
	else return itemsinfo[i - theFirstItem].texture;
}