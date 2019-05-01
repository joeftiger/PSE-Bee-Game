//
// Created by brian on 29/04/2019.
//

#ifndef PROJ_ANDROID_WALLET_H
#define PROJ_ANDROID_WALLET_H

#include "cocos2d.h"
#include <HeaderFiles/DEFINITIONS.h>
#include "HeaderFiles/Restorable.h"
#include "json/rapidjson.h"

using namespace cocos2d;


class Wallet {
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
     * @return the total money after adding a specified amount
     */
    int addMoney(int amount);

    /**
    * @return the total money after subtracting a specified amount
    */
    int subtractMoney(int amount);

    void toJSON(rapidjson::Document &doc);

   	void fromJSON(rapidjson::Document &doc);

};

#endif //PROJ_ANDROID_WALLET_H