//
// Created by brian on 25/04/2019.
//

#ifndef PROJ_ANDROID_HONEYEXTRACTORATLAS_H
#define PROJ_ANDROID_HONEYEXTRACTORATLAS_H


#include "cocos2d.h"
#include "Observer.h"
#include "Game/HoneyExtractor.h"
#include "Game/TileMapLayer.h"
#include <HeaderFiles/CHILD_NAMES.h>
#include <json/stringbuffer.h>
#include <json/writer.h>

class HoneyExtractorAtlas : public cocos2d::Node, public Observable, public Observer, public Restorable {
private:
    static HoneyExtractorAtlas*_instance;
    std::map<cocos2d::Vec2, HoneyExtractor *> _honeyExtractors;

    HoneyExtractorAtlas() = default;

    HoneyExtractorAtlas(const HoneyExtractorAtlas &);

    ~HoneyExtractorAtlas() = default;

public:
    static HoneyExtractorAtlas *getInstance();

    /**
     * Stores pointers to honey extractors in the specified vector.
     * @param honeyExtractor container for honey extractor pointers
     */
    void getHoneyExtractors(std::vector<HoneyExtractor*> &honeyExtractors);

    /**
     * Returns whether the atlas has a honey extractor  at given position.
     * @param pos position of honey extractor in tilemap
     * @return <code>true</code> if associated honey extractor object. <br><code>false</code> otherwise
     */
    bool hasHoneyExtractorAt(const Vec2 &pos);

    /**
     * Returns the honey extractor object at given position.
     * @param pos position of honey extractor in tilemap
     * @return honey extractor object
     */
    HoneyExtractor *getHoneyExtractorAt(const Vec2 &pos);

    /**
     * Notifies this Atlas, that the observable has been changed.
     * The observable should be a TileMapLayer.
     * @param observable
     */
    void notify(void *observable) override;

    /**
     * Updates all honey extractors in the atlas.
     */
    void updateHoneyExtractors (float);

    /**
     * Clears all honey extractors and resets the atlas to its original state.
     */
    void clear();

    void toJSON(rapidjson::Document &doc) override;

    void fromJSON(rapidjson::Document &doc) override;
};

#endif //PROJ_ANDROID_HONEYEXTRACTORATLAS_H
