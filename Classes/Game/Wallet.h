
#ifndef PROJ_ANDROID_WALLET_H
#define PROJ_ANDROID_WALLET_H

#include "cocos2d.h"
#include <HeaderFiles/DEFINITIONS.h>
#include "HeaderFiles/Restorable.h"
#include "json/rapidjson.h"

using namespace cocos2d;

/**
 * a singleton wallet object, that is used for interacting with money that belongs to a player
 */
class Wallet : Restorable {
private:

	bool invariant();
	int _totalMoney;

public:
	static Wallet *getInstance() {
		static auto instance = new Wallet();
		return instance;
	}

	/**
     * @return current total money
     */
    int returnTotalMoney();

	/**
	*	Resets the wallet to its original state
	*/
	void clear();

	/**
     * @return the total money after adding a specified amount
     */
    int addMoney(int amount);

    /**
    * @return the total money after subtracting a specified amount
    */
    bool subtractMoney(int amount);

    void toJSON(rapidjson::Document &doc) override;

   	void fromJSON(rapidjson::Document &doc) override;

};

#endif //PROJ_ANDROID_WALLET_H