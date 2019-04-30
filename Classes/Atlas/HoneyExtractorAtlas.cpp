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

void HoneyExtractorAtlas::getHoneyExtractors(std::vector<HoneyExtractor *> &honeyExtractors) {
    honeyExtractors.clear();
    for (auto const &pair : _honeyExtractors) {
        honeyExtractors.emplace_back(pair.second);
    }
}

bool HoneyExtractorAtlas::hasHoneyExtractorAt(const Vec2 &pos) {
    return _honeyExtractors.count(pos) != 0;
}

HoneyExtractor *HoneyExtractorAtlas::getHoneyExtractorAt(const Vec2 &pos) {
    return _honeyExtractors.at(pos);
}

void HoneyExtractorAtlas::notify(void *observable) {
    bool notifyObservers = false;

    auto layer = (TileMapLayer *) cocos2d::Director::getInstance()->getRunningScene()->getChildByName(
            TILE_MAP_LAYER_NAME);
    if (layer == nullptr) {
        layer = (TileMapLayer *) observable;
        notifyObservers = true;
    }
    auto positions = layer->getHoneyExtractors();

    // add missing honey extractors
    for (const auto &pos : positions) {
        if (!hasHoneyExtractorAt(pos)) {
            cocos2d::log("HoneyExtractorAtlas:\tCreating honey extractor at (%i, %i)", (int) pos.x, (int) pos.y);
            auto extractor = new HoneyExtractor(0);
            extractor->setPosition(pos);
            _honeyExtractors.emplace(pos, extractor);

            notifyObservers = true;
        }
    }

    if (notifyObservers) {
        cocos2d::log("HoneyExtractorAtlas:\tNotifying observers");
        this->notifyObservers();
    }
}

void HoneyExtractorAtlas::updateHoneyExtractors(float) {
    for (auto const &pair : _honeyExtractors) {
        pair.second->update();
    }
}

void HoneyExtractorAtlas::clear() {
    _honeyExtractors.clear();
}

void HoneyExtractorAtlas::toJSON(rapidjson::Document &doc) {
    for (auto const &pair : _honeyExtractors) {
        pair.second->toJSON(doc);
    }
}

void HoneyExtractorAtlas::fromJSON(rapidjson::Document &doc) {
    _honeyExtractors.clear();

    for (int i = 0; i < doc.Size(); i++) {
        rapidjson::Document subDoc;
        rapidjson::Value &data = doc[i];
        subDoc.SetObject();
        subDoc.AddMember("honeyExtractor", data, subDoc.GetAllocator());

        rapidjson::StringBuffer buffer;
        rapidjson::Writer <rapidjson::StringBuffer> writer(buffer);
        subDoc.Accept(writer);
        auto h = new HoneyExtractor();
        h->fromJSON(subDoc);

        _honeyExtractors.emplace(h->position(), h);
    }
}
