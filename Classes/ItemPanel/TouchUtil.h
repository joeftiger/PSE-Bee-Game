//
// Created by Uro on 3/29/2019.
//

#ifndef PSE_BEE_GAME_DRAGDROP_H
#define PSE_BEE_GAME_DRAGDROP_H

#include <TileMapObjects/PlaceableTile.h>
#include "cocos2d.h"
#include "TileMapObjects/Placeable.h"

using namespace cocos2d;
using namespace std;


class TouchUtil {
protected:
	bool _isDrag = false;
	Sprite *drag;
	vector<Sprite *> spriteList;
	vector<Placeable *> _placeables;

protected:
	/**
	 * Adds the given placeable object to the list of placeable objects.
	 * @param placeable
	 */
	void addToPlaceables(Placeable *placeable);

public:

	void setDrag(Point screenTouch, Point layerTouch);

	Sprite *getDrag();

	void addToSpriteList(string name, Vec2 pos, int tag, Size scale);

	bool isDrag();

	void addListTo(Layer *layer); //overloading
	void addListTo(Scene *scene);

	void setIsDrag(bool isDrag);
};


#endif //PSE_BEE_GAME_DRAGDROP_H
