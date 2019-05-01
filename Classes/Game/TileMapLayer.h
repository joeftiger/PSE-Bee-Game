//
// Created by julius on 21.03.19.
//

#ifndef PSE_BEE_GAME_TILEMAPLAYER_H
#define PSE_BEE_GAME_TILEMAPLAYER_H

#include <TileMapObjects/Placeable.h>
#include <Resources/Sprites.h>
#include "cocos2d.h"
#include "Observable.h"

USING_NS_CC;

// pre-declare to <fix> "Placeable has no type."
class Placeable;

class TileMapLayer : public cocos2d::Layer, public Observable {
private:
	TMXTiledMap *_tileMap;
	TMXLayer *_objectLayer;
	TMXLayer *_obstructionLayer;


	void loadMap();

	/**
	 * Initialzes the obstruction layer accordin to obstructing tiles in the object layer
	 */
	void initObstructionLayer();

public:

	bool useSD = false;

	virtual bool init() override;

	ssize_t getTreeCount();

	ssize_t getFlowerCount();

	/**
	 * Returns the positions of each beehive on the tile map.
	 * @return a list of beehive-positions
	 */
	std::vector<Vec2> getBeeHives();
	std::vector<Vec2> getHoneyExtractors();

	TMXTiledMap *getMap();

	TMXLayer *getLayer();

	Vec2 getTilePosition(Vec2 pos);

	Vec2 inTileMapBounds(const Vec2 &pos);

	/**
	 * Checks whether the given placeable object can be placed at the specified position.
	 * If the area around the position is obstructed, <code>false</code> will be returned.
	 * @param placeable the object to place
	 * @param position  the position to place (in tile coordinates)
	 * @return <code>true</code> if not obstructed. <br><code>false</code> otherwise.
	 */
	bool canPlace(Placeable *placeable, Vec2 &position);

	/**
	 *
	 * @param placeable
	 * @param position
	 */
	void place(Placeable *placeable, Vec2 &position);

	/**
	 * Returns whether the tile at specified position can be replaced or not (e.g. beehive/tree on this tile)
	 * @param position position in tile coordinates
	 * @param gid the gid of the new tile
	 * @return <code>true</code> if tile may be placed. <br>
	 * 		   <code>false</code> if the position is obstructed.
	 */
	bool canPlaceTile(const Vec2 &position, int gid);

	/**
	 * Places the given tile (gid) at the given position (forced).
	 * @param position position in tile coordinates
	 * @param gid tile gid
	 */
	void placeTile(const Vec2 &position, const int &gid);

	/**
	 * Returns whether a sprite with given size and ID can be placed at the specified position.
	 * @param position position in tile coordinates
	 * @param size size of sprite (will be counted backwards from position)
	 * @param id sprite id
	 * @return <code>true</code> if sprite can be placed. <br>
	 * 		   <code>false</code> if not.
	 */
	bool canPlaceSprite(const Vec2 &position, const Size &size, Sprites::SpriteID id);

	/**
	 * Places the sprite with given size and ID to the specified position.
	 * @param position position in tile coordinates
	 * @param size size of sprite (will be counted backwards from position);
	 * @param id sprite id
	 */
	void placeSprite(const Vec2 &position, const Size &size, Sprites::SpriteID id);

	/**
	 * Shows / hides the obstruction layer
	 * @param visible <code>true</code> if the obstruction layer is visible. <br>
	 * 				  <code>false</code> if the obstruction layer is hidden.
	 */
	void showObstructions(bool visible);


	// implement the "static create()" method manually
	CREATE_FUNC(TileMapLayer)
};


#endif //PSE_BEE_GAME_TILEMAPLAYER_H
