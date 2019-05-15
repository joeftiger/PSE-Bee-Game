
#include "StoryScene.h"
#include "Popup.h"
#include "Game/Time.h"
#include "SaveLoad/SaveLoad.h"
#include "../Settings.h"

void StoryScene::init() {
	if (SaveLoad::storySaveExists()) {
		SaveLoad::loadStory();
	}
}

UICustom::Popup* StoryScene::createPopup(int id) {

	auto settings = Settings::getInstance();

	if (!settings->getAsBool(Settings::Show_Tutorial)){
		return nullptr;
	}

    switch (id) {
        case 0: //Intro
            if (firstTime0) {
                auto popup = UICustom::Popup::createAsMessage("GROSSVATER",
                                     "Hallo mein Enkel, schön bist du da. Ich hätte eine bitte an dich.\n"
                                     "Kannst du auf meine Bienen aufpassen? Keine Angst, sie stechen nicht.");
                firstTime0 = false;
                SaveLoad::saveStory();
                return popup;
            }
            else return nullptr;

        case 1: //Beehive Info
            if (firstTime1) {
                auto popup = UICustom::Popup::createAsMessage("GROSSVATER",
                                      "Hier findest du Informationen über deine Bienenstöcke.\n"
                                      "Überprüfe möglichst oft die Gesundheit der Bienen und ihre Nahrung!");
                firstTime1 = false;
                SaveLoad::saveStory();
                return popup;
            }
            else return nullptr;
	
        case 2: //Varroa Info
            if (firstTime2) {
                auto popup = UICustom::Popup::createAsMessage("GROSSVATER",
                                      "Achtung! Deine Bienen sind an Varroa Milben erkrankt.\n"
                                      "Schau doch im Shop nach, ob du etwas dagegen finden kannst.");
                firstTime2 = false;
                SaveLoad::saveStory();
                return popup;
            }
            else return nullptr;
			
        case 3: //Shop Info
            if (firstTime3) {
                auto popup = UICustom::Popup::createAsMessage("GROSSVATER",
                                      "Hier kannst du alles kaufen was du für die Bienen brauchst.\n"
                                      "Ziehe dazu einfach was du kaufen willst auf die Karte.");
                firstTime3 = false;
                SaveLoad::saveStory();
                return popup;
            }
            else return nullptr;
			
        case 4: //Fall/Winter Season Info
            if (firstTime4) {
                auto popup = UICustom::Popup::createAsMessage("GROSSVATER",
                                      "Der Winter naht.\n"
                                      "Die Bienen brauchen genug Nahrung um den Winter zu überleben");
                firstTime4 = false;
                SaveLoad::saveStory();
                return popup;
            }
            else return nullptr;

        default:
            return nullptr;
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
    const rapidjson::Value &story = doc[0];
    assert(story["firstTime0"].IsBool());
	cocos2d::log("0 %d", firstTime0);
    firstTime0 = story["firstTime0"].GetBool();
	cocos2d::log("0 %d", firstTime0);
    assert(story["firstTime1"].IsBool());
    firstTime1 = story["firstTime1"].GetBool();
    assert(story["firstTime2"].IsBool());
    firstTime2 = story["firstTime2"].GetBool();
    assert(story["firstTime3"].IsBool());
    firstTime3 = story["firstTime3"].GetBool();
    assert(story["firstTime4"].IsBool());
    firstTime4 = story["firstTime4"].GetBool();
}

void StoryScene::skipTutorial(){ // todo: implement button in options scene
    firstTime0 = false;
    firstTime1 = false;
    firstTime2 = false;
    firstTime3 = false;
    firstTime4 = false;
    SaveLoad::saveStory();
}