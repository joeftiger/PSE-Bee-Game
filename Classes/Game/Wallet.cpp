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
	return _totalMoney;
}

/** TODO toJSON and fromJSON for loading adn saving of money
void Wallet::toJSON(rapidjson::Document &doc) {

	rapidjson::Value obj(rapidjson::kObjectType);
	obj.AddMember("_totalMoney", _totalMoney, doc.GetAllocator());
	doc.PushBack(obj, doc.GetAllocator());

}

void Wallet::fromJSON(rapidjson::Document &doc) {

	assert(doc.HasMember("totalMoney"));
	const rapidjson::Value &totalMoney = doc["totalMoney"];

}
*/