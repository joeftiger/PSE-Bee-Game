//
// Created by julius on 22.03.19.
//

#ifndef PSE_BEE_GAME_PLAYER_H
#define PSE_BEE_GAME_PLAYER_H

#include <vector>
#include <Shop/Items.h>
#include "BeeHive.h"
#include "Observer.h"
#include "Observable.h"

class Player : public Observer, public Observable {
private:
    static Player *_instance;
    std::vector<BeeHive *> *_beeHives;
    std::unordered_map<Items, size_t> *_inventory;

    Player() = default;
    Player(const Player&);
    ~Player() = default;

    bool invariant();

public:
    static Player* getInstance();

    /**
     * Returns the total raw honey currently in the BeeHiveAtlas
     * @return
     */
    float TotalRawHoney();

    /**
     * Returns the item inventory of the player.
     * @return the inventory
     */
    std::unordered_map<Items, size_t> *getInventory();

    /**
     * Notifies this player, that the beehives have changed.
     * @param pVoid
     */
	void notify(void *pVoid) override;
};

#endif //PSE_BEE_GAME_PLAYER_H
