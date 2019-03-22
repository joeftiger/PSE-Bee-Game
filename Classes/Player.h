//
// Created by julius on 22.03.19.
//

#ifndef PSE_BEE_GAME_PLAYER_H
#define PSE_BEE_GAME_PLAYER_H

#include <vector>
#include "BeeHive.h"

class Player {
private:
    static Player *_instance;
    std::vector<BeeHive> _beeHives;

    Player() = default;
    Player(const Player&);
    ~Player() = default;

    bool invariant();

public:
    static Player* getInstance();

    float TotalRawHoney();
};

#endif //PSE_BEE_GAME_PLAYER_H
