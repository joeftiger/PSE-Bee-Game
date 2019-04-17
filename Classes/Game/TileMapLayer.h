//
// Created by julius on 21.03.19.
//

#ifndef PSE_BEE_GAME_TILEMAPLAYER_H
#define PSE_BEE_GAME_TILEMAPLAYER_H

#include <TileMapObjects/Placeable.h>
#include "cocos2d.h"
#include "Observable.h"

USING_NS_CC;

// pre-declare to <fix> "Placeable has no type."
class Placeable;

class TileMapLayer : public cocos2d::Layer, public Observable {
private:
	TMXTiledMap *_tileMap;

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
	std::vector <Vec2> getBeeHives();

	TMXTiledMap *getMap();

	TMXLayer *getLayer();

	Vec2 getTilePosition(Vec2 pos);

	Vec2 inTileMapBounds(const Vec2& pos);

	/**
	 * Checks whether the tile at specified position can be replaced or not (e.g. beehive/tree on this tile)
	 * @param position the position of the tile
	 * @param gid the gid of the new tile
	 * @return <code>true</code> if tile may be placed. <br>
	 * 		   <code>false</code> if the position is obstructed.
	 */
	bool canPlaceTile(const Vec2 &position, int gid);

	/**
	 * TODO: Should the placing be forced?
	 * Places the given tile (gid) at the given position (forced).
	 * @param position tile position
	 * @param gid tile gid
	 */
	void placeTile(const Vec2 &position, int gid);

	bool canPlace(const Placeable &placeable, const Vec2 &position);

	void place(const Placeable &placeable, const Vec2 &position);

	void placeTree(const Vec2 &position, int id);


	/**
	 * Shows / hides the obstruction layer
	 * @param visible <code>true</code> if the obstruction layer is visible. <br>
	 * 				  <code>false</code> if the obstruction layer is hidden.
	 */
	void showObstructions(bool visible);

	void booleanInverter();

	// implement the "static create()" method manually
	CREATE_FUNC(TileMapLayer)
};


#endif //PSE_BEE_GAME_TILEMAPLAYER_H
