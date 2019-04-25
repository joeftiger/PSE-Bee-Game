//
// Created by brian on 25/04/2019.
//

#include "HoneyExtractorAtlas.h"

HoneyExtractorAtlas *HoneyExtractorAtlas::_instance = nullptr;

HoneyExtractorAtlas *HoneyExtractorAtlas::getInstance() {
    if (!_instance) {
        cocos2d::log("HoneyExtractorAtlas:\tCreating instance");
        _instance = new HoneyExtractorAtlas;
    }

    return _instance;
}

/*void HoneyExtractorAtlas::getBeeHives(std::vector<BeeHive *> &beeHives) {
    beeHives.clear();
    for (auto const &pair : _beeHives) {
        beeHives.emplace_back(pair.second);
    }
}*/

/*bool HoneyExtractorAtlas::hasBeeHiveAt(const Vec2 &pos) {
    return _beeHives.count(pos) != 0;
}*/

/*BeeHive *HoneyExtractorAtlas::getBeeHiveAt(const Vec2 &pos) {
    return _beeHives.at(pos);
}*/

void HoneyExtractorAtlas::notify(void *observable) {
    bool notifyObservers = false;

    auto layer = (TileMapLayer *) cocos2d::Director::getInstance()->getRunningScene()->getChildByName(
            TILE_MAP_LAYER_NAME);
    if (layer == nullptr) {
        layer = (TileMapLayer *) observable;
        notifyObservers = true;
    }
    //auto positions = layer->getBeeHives();

    // add missing beehives
/*    for (const auto &pos : positions) {
        if (!hasBeeHiveAt(pos)) {
            cocos2d::log("HoneyExtractorAtlas:\tCreating beehive at (%i, %i)", (int) pos.x, (int) pos.y);
            auto hive = new BeeHive();
            hive->setPosition(pos);
            _beeHives.emplace(pos, hive);

            notifyObservers = true;
        }
    }*/

    if (notifyObservers) {
        cocos2d::log("HoneyExtractorAtlas:\tNotifying observers");
        this->notifyObservers();
    }
}

/*void HoneyExtractorAtlas::updateBeeHives(float) {
    for (auto const &pair : _beeHives) {
        pair.second->update();
    }
}*/

void HoneyExtractorAtlas::clear() {
    _honeyExtractor.clear();
}

void HoneyExtractorAtlas::toJSON(rapidjson::Document &doc) {
    // TODO Fix following line
    for (auto const &pair : _honeyExtractor) {
        pair.second->toJSON(doc);
    }
}

void HoneyExtractorAtlas::fromJSON(rapidjson::Document &doc) {
   // _beeHives.clear();

    for (int i = 0; i < doc.Size(); i++) {
        rapidjson::Document subDoc;
        rapidjson::Value &data = doc[i];
        subDoc.SetObject();
        subDoc.AddMember("honeyExtractor", data, subDoc.GetAllocator());

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        subDoc.Accept(writer);
        auto h = new HoneyExtractor();
        h->fromJSON(subDoc);

        _honeyExtractor.emplace(h->position(), h);
    }
}
