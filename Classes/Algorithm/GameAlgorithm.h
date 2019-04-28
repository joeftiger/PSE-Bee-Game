//
// Created by uro on 4/25/19.
//

#ifndef PSE_BEE_GAME_GAMEALGORITHM_H
#define PSE_BEE_GAME_GAMEALGORITHM_H

#define HONEY_PER_BEE (14400*45000)/6/30/24/60/60/50000;
#define BEES_PER_UPDATE 62;
#define BEES_DEAD_PER_UPDATE 7;
#define VARROA_KILL_RATE 0.03f;

#include "Game/BeeHive.h"
#include "Atlas/BeeHiveAtlas.h"


class GameAlgorithm {
private:
    static GameAlgorithm *_instance;
    std::vector<BeeHive*> _beeHives;
    int _varroaCounter;

public:
    static GameAlgorithm *getInstance();

    /**
     * Returns the amount of honey produced every second, depending on the amount of bees.
     *
     * @param bees
     * @return
     */
    double honeyProduction(int bees);

    int nextBees(int bees, int varroa);
    int nextVarroa(int varroa);

    void setBeeHives();

};


#endif //PSE_BEE_GAME_GAMEALGORITHM_H
