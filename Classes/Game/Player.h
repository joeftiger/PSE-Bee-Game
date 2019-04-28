//
// Created by julius on 22.03.19.
//

#ifndef PSE_BEE_GAME_PLAYER_H
#define PSE_BEE_GAME_PLAYER_H

#include <vector>
#include <TileMapObjects/Placeable.h>
#include "BeeHive.h"
#include "Atlas/BeeHiveAtlas.h"
#include "HoneyExtractor.h"
#include "Atlas/HoneyExtractorAtlas.h"
#include "Observer.h"
#include "Observable.h"

class Player : public Observer, public Observable {
private:
	static Player *_instance;
	std::vector<BeeHive *> _beeHives;
	std::vector<HoneyExtractor *> _honeyExtractors;
	std::unordered_map<Placeable, size_t> *_inventory;

	Player() = default;

	Player(const Player &);

	~Player() = default;

	bool invariant();

public:
	static Player *getInstance();
	int amount;
	int totalMoney;

	/**
	 * @return the total raw honey currently in the BeeHiveAtlas
	 */
	float totalRawHoney();

	/**
     * @return current total money
     * TODO: Put money somewhere else to make it more sensible???
     */
    int returnTotalMoney();

	/**
     * @return the total money after adding a specified amount
     */
	int addMoney(int amount);

	/**
     * @return the total money after subtracting a specified amount
     */
	int subtractMoney(int amount);
	/**
	 * Returns the item inventory of the player.
	 * @return the inventory
	 */
	std::unordered_map<Placeable, size_t> *getInventory();

	/**
	 * Notifies this player, that the beehives or honey extractors have changed.
	 * @param pVoid
	 */
	void notify(void *pVoid) override;
};

#endif //PSE_BEE_GAME_PLAYER_H
