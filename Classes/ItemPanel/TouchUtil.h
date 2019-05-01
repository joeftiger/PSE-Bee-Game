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
	Placeable *_draggedPlaceable;
	Sprite *_draggedSprite;

	/**
	 * I use a hashmap, because each placeable::getSprite() creates a new Sprite each time -> we can therefore
	 * create distinct sprites for this node's children and the dragged placeable sprite.
	 */
	std::map<Sprite *, Placeable *> _spritesToPlaceables;
	vector<Sprite *> _spriteList;
	vector<Placeable *> _placeables;

protected:
	/**
	 * Adds the given placeable object to the list of placeable objects.
	 * @param placeable
	 */
	void addToPlaceables(Placeable *placeable);

public:

	/**
	 * Sets the dragged content to the placeable, which the given touch position touches.
	 * @param touchPos touch position (local coordinate)
	 */
	void setDrag(const Vec2 &touchPos);

	Placeable *getDraggedPlaceable();

	Sprite *getDraggedSprite();

	bool isDrag();

	void addListTo(Layer *layer); //overloading
	void addListTo(Scene *scene);

	void setIsDrag(bool isDrag);
};


#endif //PSE_BEE_GAME_DRAGDROP_H
