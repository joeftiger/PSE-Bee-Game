
#ifndef DRAGDROP_H
#define DRAGDROP_H

#include <TileMapObjects/PlaceableTile.h>
#include "cocos2d.h"
#include "TileMapObjects/Placeable.h"

using namespace cocos2d;
using namespace std;

/**
 * TouchUtilities to deal with dragging onto the tileMap
 */
class TouchUtil {
protected:
	bool _isDrag = false;
	Placeable *_draggedPlaceable;
	Sprite *_draggedSprite;

	/**
	 * Using a hashmap, because each placeable::getSprite() creates a new Sprite
	 * thus we can create distinct sprites for this node's children and the dragged placeable sprite.
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


#endif //DRAGDROP_H
