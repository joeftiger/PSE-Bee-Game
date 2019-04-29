//
// Created by brian on 29/04/2019.
//

#ifndef PROJ_ANDROID_WALLET_H
#define PROJ_ANDROID_WALLET_H

#endif //PROJ_ANDROID_WALLET_H


class Wallet {
private:
	static Wallet *_instance;

	bool invariant();

	int _totalMoney;
public:


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

};
