//
// Created by brian on 29/04/2019.
//

#include "Wallet.h"




bool Wallet::invariant() {
	return true;
}


int Wallet::addMoney(int amount) {
	_totalMoney += amount;
	return _totalMoney;
}

int Wallet::subtractMoney(int amount) {
	_totalMoney -= amount;
	return _totalMoney;
}

int Wallet::returnTotalMoney() {
//	for (auto he : _honeyExtractors) {
//		totalMoney += he->totalMoney();
//	}
	return _totalMoney;
}