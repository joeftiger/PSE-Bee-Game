

#ifndef PSE_BEE_GAME_GAMEALGORITHM_H
#define PSE_BEE_GAME_GAMEALGORITHM_H

#define HONEY_PER_BEE 9/5/12/60;
#define FOOD_EATEN_PER_BEE 9/10/12/60;
#define BEES_PER_UPDATE 62*3;
#define BEES_DEAD_PER_UPDATE 7*3;
#define VARROA_KILL_RATE 0.03f;

#include "Game/BeeHive.h"
#include "Atlas/BeeHiveAtlas.h"

/**
 * Orcestrates gameplay algorithms.
 */
class GameAlgorithm {
private:
    static GameAlgorithm *_instance;
    std::vector<BeeHive*> _beeHives;
    int _varroaCounter;

public:
    static GameAlgorithm *getInstance();

    /**
     * Returns the amount of honey produced every second, depending on the amount of bees.
     * Called @BeeHive update.
     *
     * @param bees
     * @return
     */
    float honeyProduction(int bees, int food);

    /**
     * Returns the amount to add or subtract from the bees of a beehive.
     * Called @BeeHive update.
     *
     * @param bees
     * @param varroa
     * @return
     */
    int nextBees(int bees, int varroa, int food, int honey);

    /**
     * Doubles the amount of varroa of a beehive every 10 days in-game time.
     * Called @BeeHive update.
     *
     * @param varroa
     * @return
     */
    int nextVarroa(int varroa);

    /**
     * Returns the amount of food consumed by bees.
     *
     * @param bees
     */
    int foodConsumption(int bees);

    void setBeeHives();

};


#endif //PSE_BEE_GAME_GAMEALGORITHM_H
