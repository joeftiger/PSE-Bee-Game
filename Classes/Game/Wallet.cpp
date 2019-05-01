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

void Wallet::toJSON(rapidjson::Document &doc) {

	rapidjson::Value obj(rapidjson::kObjectType);
	obj.AddMember("totalMoney", _totalMoney, doc.GetAllocator());
	doc.PushBack(obj, doc.GetAllocator());

}

void Wallet::fromJSON(rapidjson::Document &doc) {

	assert(doc.IsArray());

	const rapidjson::Value &m = doc[0];

	assert(m["totalMoney"].IsInt());
	_totalMoney = m["totalMoney"].GetInt();

}
