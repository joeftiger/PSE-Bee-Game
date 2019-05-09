
#include "StoryScene.h"
#include "Popup.h"
#include "Game/Time.h"

bool StoryScene::init() {

	if (!Node::init()) {
		return false;

	}

	//if () //todo: if no "story.json" save state file exists, create one with all "firstTime" states set to true.
	//else () //todo: if "story.json" exists, import its states.
	//todo: Maybe able to set all false with skip tutorial button.


	return true;
}

UICustom::Popup* StoryScene::createPopup(int id) {
    switch (id) {
        case 0: //Intro
            if (firstTime0) {
                return UICustom::Popup::createAsMessage("GROSSVATER",
                                                        "Hallo mein Enkel, schön bist du da. Ich hätte eine bitte an dich.\n"
                                                        "Kannst du auf meine Bienen aufpassen? Nur bis ich wieder da bin...");

            }
            firstTime0 = false; //todo: save state to "story.json"

        case 1: //Beehive Info
            if (firstTime1) {
                return UICustom::Popup::createAsMessage("GROSSVATER", "Hi Brian please insert beehive info here\n"
                                                                      "...and if you need another line here :) ");
            }
        case 2: //Varroa Info
            if (firstTime2) {
                return UICustom::Popup::createAsMessage("GROSSVATER", "Hi Brian please insert varroa info here\n"
                                                                      "and if you need another line here :) ");
            }
        case 3: //Shop Info
            if (firstTime3) {
                return UICustom::Popup::createAsMessage("GROSSVATER", "Hi Brian please insert shop info here\n"
                                                                      "and if you need another line here :) ");
            }
        case 4: //Fall/Winter Season Info
            if (firstTime4) {
                return UICustom::Popup::createAsMessage("GROSSVATER",
                                                        "Hi Brian please insert first fall/winter season info here\n"
                                                        "and if you need another line here :) ");
            }

    }
}

void StoryScene::toJSON(rapidjson::Document &doc) {

    rapidjson::Value obj(rapidjson::kObjectType);
    obj.AddMember("firstTime0", firstTime0, doc.GetAllocator());
    obj.AddMember("firstTime1", firstTime1, doc.GetAllocator());
    obj.AddMember("firstTime2", firstTime2, doc.GetAllocator());
    obj.AddMember("firstTime3", firstTime3, doc.GetAllocator());
    obj.AddMember("firstTime4", firstTime4, doc.GetAllocator());
    doc.PushBack(obj, doc.GetAllocator());

}

void StoryScene::fromJSON(rapidjson::Document &doc) {
    assert(doc.IsArray());
    const rapidjson::Value &beeHive = doc[""];

    //assert(beeHive.HasMember("_beesAlive"));
    assert(beeHive["_beesAlive"].IsInt());
    _beesAlive = beeHive["_beesAlive"].GetInt();

    assert(beeHive["_varroaAlive"].IsInt());
    _varroaAlive = beeHive["_varroaAlive"].GetInt();

    assert(beeHive["_rawHoney"].IsFloat());
    _rawHoney = beeHive["_rawHoney"].GetFloat();

    assert(beeHive["_posX"].IsInt());
    _position.x = beeHive["_posX"].GetInt();

    assert(beeHive["_posY"].IsInt());
    _position.y = beeHive["_posY"].GetInt();
}