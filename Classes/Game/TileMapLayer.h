
#ifndef PSE_BEE_GAME_TILEMAPLAYER_H
#define PSE_BEE_GAME_TILEMAPLAYER_H

#include <TileMapObjects/Placeable.h>
#include <Resources/Tiles.h>
#include <Resources/Sprites.h>
#include "cocos2d.h"
#include "Observable.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "HeaderFiles/Restorable.h"

USING_NS_CC;

// pre-declare to <fix> "Placeable has no type."
class Placeable;

class TileMapLayer : public cocos2d::Layer, public Observable, public Restorable {
private:
	TMXTiledMap *_tileMap;
	TMXLayer *_objectLayer;
	TMXLayer *_obstructionLayer;

	std::vector<Sprite *> _spriteList;

	void loadMap();

	/**
	 * Initializes the obstruction layer accordin to obstructing tiles in the object layer
	 */
	void initObstructionLayer();

public:
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

	/**
	 * Returns the layer containing all objects (NOT the obstruction layer)
	 * @return object layer
	 */
	TMXLayer *getLayer();

	/**
	 * Returns the list of child sprites (trees, etc.)
	 * @return list of sprites
	 */
	std::vector<Sprite *> getSpriteList();

	Vec2 getTilePosition(Vec2 pos);

	/**
     * Checks whether the given vector is out of bounds
     * @return (0,0) if out of bounds, otherwise the vector itself
     */
	Vec2 inTileMapBounds(const Vec2 &pos);

	/**
	* Checks whether a given vector touches the tilemap
	*/
	bool isVectorOnTileMap(Vec2 pos);

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
	 * @return <code>true</code> if tile may be placed. <br>
	 * 		   <code>false</code> if the position is obstructed.
	 */
	bool canPlaceTile(const Vec2 &position);

	/**
	 * Places the given tile (gid) at the given position (forced).
	 * @param position position in tile coordinates
	 * @param gid tile gid
	 */
	void placeTile(const Vec2 &position, Tiles::TileGID &gid);

	/**
	 * Returns whether a sprite with given size and ID can be placed at the specified position.
	 * @param position position in tile coordinates
	 * @param size size of sprite (will be counted backwards from position)
	 * @param id sprite id
	 * @return <code>true</code> if sprite can be placed. <br>
	 * 		   <code>false</code> if not.
	 */
	bool canPlaceSprite(const Vec2 &position, const Size &size);

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

	void toJSON(rapidjson::Document &doc);

	void fromJSON(rapidjson::Document &doc);

	// implement the "static create()" method manually
	CREATE_FUNC(TileMapLayer)
};


#endif //PSE_BEE_GAME_TILEMAPLAYER_H


