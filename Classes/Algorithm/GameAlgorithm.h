

#ifndef GAMEALGORITHM_H
#define GAMEALGORITHM_H

#define HONEY_PER_BEE 0.0025;
#define FOOD_EATEN_PER_BEE 0.00125;
#define BEES_PER_UPDATE 186;
#define BEES_DEAD_PER_UPDATE 21;
#define VARROA_KILL_RATE 0.25f;

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
    int nextBees(float bees, float varroa, float food, float honey);

    /**
     * Doubles the amount of varroa of a beehive every 10 days in-game time.
     * Called @BeeHive update.
     *
     * @param varroa
     * @return
     */
    int nextVarroa(float bees, int varroa);

    /**
     * Returns the amount of food consumed by bees.
     *
     * @param bees
     */
    int foodConsumption(int bees);

    void setBeeHives();

};


#endif //GAMEALGORITHM_H
