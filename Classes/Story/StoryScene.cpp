
#include "StoryScene.h"
#include "Popup.h"
#include "Game/Time.h"
#include "SaveLoad/SaveLoad.h"

bool StoryScene::init() {

	if (!Node::init()) {
		return false;

	}

    // Load states or create state file if none exists.
	auto fs = FileUtils::getInstance();
    std::string path = fs->getWritablePath();
    if (fs->isFileExist(path + "saves/story.json")){
        SaveLoad::loadStory();
    } else {
        firstTime0 = true;
        firstTime1 = true;
        firstTime2 = true;
        firstTime3 = true;
        firstTime4 = true;
        SaveLoad::saveStory();
    }


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
    const rapidjson::Value &story = doc["story"];

    assert(story["firstTime0"].IsBool());
    firstTime0 = story["firstTime0"].GetBool();
    assert(story["firstTime1"].IsBool());
    firstTime1 = story["firstTime1"].GetBool();
    assert(story["firstTime2"].IsBool());
    firstTime2 = story["firstTime2"].GetBool();
    assert(story["firstTime3"].IsBool());
    firstTime3 = story["firstTime3"].GetBool();
    assert(story["firstTime4"].IsBool());
    firstTime4 = story["firstTime4"].GetBool();
}

void StoryScene::skipTutorial(){
    firstTime0 = false;
    firstTime1 = false;
    firstTime2 = false;
    firstTime3 = false;
    firstTime4 = false;
    SaveLoad::saveStory();
}