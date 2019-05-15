
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
            if (seenPopUp0) {
                auto popup = UICustom::Popup::createAsMessage("GROSSVATER",
                                     "Hallo mein Enkel, schön bist du da. Ich hätte eine bitte an dich.\n"
                                     "Kannst du auf meine Bienen aufpassen? Keine Angst, sie stechen nicht.");
                seenPopUp0 = false;
                SaveLoad::saveStory();
                return popup;
            }
            else return nullptr;

        case 1: //Beehive Info
            if (seenPopUp1) {
                auto popup = UICustom::Popup::createAsMessage("GROSSVATER",
                                      "Hier findest du Informationen über deine Bienenstöcke.\n"
                                      "Überprüfe möglichst oft die Gesundheit der Bienen und ihre Nahrung!");
                seenPopUp1 = false;
                SaveLoad::saveStory();
                return popup;
            }
            else return nullptr;
	
        case 2: //Varroa Info
            if (seenPopUp2) {
                auto popup = UICustom::Popup::createAsMessage("GROSSVATER",
                                      "Achtung! Deine Bienen sind an Varroa Milben erkrankt.\n"
                                      "Schau doch im Shop nach, ob du etwas dagegen finden kannst.");
                seenPopUp2 = false;
                SaveLoad::saveStory();
                return popup;
            }
            else return nullptr;
			
        case 3: //Shop Info
            if (seenPopUp3) {
                auto popup = UICustom::Popup::createAsMessage("GROSSVATER",
                                      "Hier kannst du alles kaufen was du für die Bienen brauchst.\n"
                                      "Ziehe dazu einfach was du kaufen willst auf die Karte.");
                seenPopUp3 = false;
                SaveLoad::saveStory();
                return popup;
            }
            else return nullptr;
			
        case 4: //Fall/Winter Season Info
            if (seenPopUp4) {
                auto popup = UICustom::Popup::createAsMessage("GROSSVATER",
                                      "Der Winter naht.\n"
                                      "Die Bienen brauchen genug Nahrung um den Winter zu überleben");
                seenPopUp4 = false;
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
    obj.AddMember("seenPopUp0", seenPopUp0, doc.GetAllocator());
    obj.AddMember("seenPopUp1", seenPopUp1, doc.GetAllocator());
    obj.AddMember("seenPopUp2", seenPopUp2, doc.GetAllocator());
    obj.AddMember("seenPopUp3", seenPopUp3, doc.GetAllocator());
    obj.AddMember("seenPopUp4", seenPopUp4, doc.GetAllocator());
    doc.PushBack(obj, doc.GetAllocator());
}

void StoryScene::fromJSON(rapidjson::Document &doc) {
    assert(doc.IsArray());
    const rapidjson::Value &story = doc[0];
    assert(story["seenPopUp0"].IsBool());
	cocos2d::log("0 %d", seenPopUp0);
    seenPopUp0 = story["seenPopUp0"].GetBool();
	cocos2d::log("0 %d", seenPopUp0);
    assert(story["seenPopUp1"].IsBool());
    seenPopUp1 = story["seenPopUp1"].GetBool();
    assert(story["seenPopUp2"].IsBool());
    seenPopUp2 = story["seenPopUp2"].GetBool();
    assert(story["seenPopUp3"].IsBool());
    seenPopUp3 = story["seenPopUp3"].GetBool();
    assert(story["seenPopUp4"].IsBool());
    seenPopUp4 = story["seenPopUp4"].GetBool();
}

void StoryScene::skipTutorial(){ // todo: implement button in options scene
    seenPopUp0 = false;
    seenPopUp1 = false;
    seenPopUp2 = false;
    seenPopUp3 = false;
    seenPopUp4 = false;
    SaveLoad::saveStory();
}