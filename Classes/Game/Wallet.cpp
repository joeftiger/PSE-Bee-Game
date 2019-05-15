
#include "Wallet.h"
#include "GameScene.h"

bool Wallet::invariant() {
	return true;
}


int Wallet::addMoney(int amount) {
	_totalMoney += amount;
	return _totalMoney;
}

bool Wallet::subtractMoney(int amount) {
    if (_totalMoney >= amount) {
	    _totalMoney -= amount;
	    return true;
    }
    else {
        auto noMoneyLabel = Label::createWithTTF("Du hast nicht genug Geld", FONT, 40);
        noMoneyLabel->enableOutline(Color4B::BLACK, 1);
        auto winSize = Director::getInstance()->getWinSize();
        noMoneyLabel->setPosition(winSize.width / 2 , winSize.height * 0.75f);
        auto scene = (GameScene*) Director::getInstance()->getRunningScene();
        scene->getCameraContainer()->addChild(noMoneyLabel, 1000);
        noMoneyLabel->runAction(Sequence::create(FadeTo::create(4.0f, 0), RemoveSelf::create(), NULL));
	    return false;
    }
}

int Wallet::returnTotalMoney() {
	return _totalMoney;
}

void Wallet::clear() {
	_totalMoney = 0;
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
