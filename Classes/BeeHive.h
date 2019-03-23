//
// Created by julius on 22.03.19.
//

#ifndef PSE_BEE_GAME_BEEHIVE_H
#define PSE_BEE_GAME_BEEHIVE_H

static const int MAX_BEES = 20000;
static const float MAX_RAW_HONEY = 2000;

class BeeHive {
private:
    int _beesAlive;
    int _varoaAlive;

    float _rawHoney;

    bool invariant();

public:
    /**
     * Creates a new healthy beehive with 100 bees.
     */
    explicit BeeHive();

    /**
     * Creates a new healthy beehive.
     * @param bees the initial number of bees
     */
    explicit BeeHive(int bees);

    /**
     * Creates a new infected beehive
     * @param bees  the initial number of bees
     * @param varoa  the initial number of varoa
     */
    explicit BeeHive(int bees, int varoa);

    /**
     * Returns whether this beehive is empty and has no bees in it.
     * @return <code>true</code> if no bees in this hive.
     */
    bool isEmpty();

    /**
     * Returns whether this beehive has maxed out its bee population.
     * @return <code>true</true> if beehive is full.
     */
    bool isFull();

    int beesAlive();

    int varoaAlive();

    /**
     * Returns the total raw honey currently in the beehive.
     * @return the total raw honey
     */
    float rawHoney();

    /**
     * Returns whether the beehive has maxed out its total raw honey.
     * @return <code>true</code> if raw honey storage is full
     */
    bool hasFullStorage();

    /**
     * Takes and removes the total raw honey currently in the beehive.
     * @return the total raw honey
     */
    float takeRawHoney();

    /**
     * Takes and removes the specified amount from the raw honey currently in the beehive.
     * @param amount the amount to take (must be in between <code>[0, rawHoney()]</code>)
     * @return the amount taken
     * @throws std::out_of_range() if amount is an invalid value
     */
    float takeRawHoney(float amount);

    /**
     *
     */
    void update();
};

#endif //PSE_BEE_GAME_BEEHIVE_H
