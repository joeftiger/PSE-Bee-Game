
#include "StoryScene.h"
#include "Popup.h"
#include "Game/Time.h"
#include "SaveLoad/SaveLoad.h"
#include "../Settings.h"

UICustom::Popup* StoryScene::createPopup(int id) {

	auto settings = Settings::getInstance();

	if (!settings->getAsBool(Settings::Show_Tutorial)){
		return nullptr;
	}

    switch (id) {
        case 0: //Intro
            if (popups[id]) {
                auto popup = UICustom::Popup::createAsMessage("GROSSVATER",
                                     "Hallo mein Enkel, schön bist du da. Ich hätte eine bitte an dich.\n"
                                     "Kannst du auf meine Bienen aufpassen? Keine Angst, sie stechen nicht.");
                popups[id] = false;
                SaveLoad::saveStory();
                return popup;
            }
            return nullptr;

        case 1: //Beehive Info
            if (popups[id]) {
                auto popup = UICustom::Popup::createAsMessage("GROSSVATER",
                                      "Hier findest du Informationen über deine Bienenstöcke.\n"
                                      "Überprüfe möglichst oft die Gesundheit der Bienen und ihre Nahrung!");
                popups[id] = false;
                SaveLoad::saveStory();
                return popup;
            }
            return nullptr;
	
        case 2: //Varroa Info
            if (popups[id]) {
                auto popup = UICustom::Popup::createAsMessage("GROSSVATER",
                                      "Achtung! Deine Bienen sind an Varroa Milben erkrankt.\n"
                                      "Schau doch im Shop nach, ob du etwas dagegen finden kannst.");
                popups[id] = false;
                SaveLoad::saveStory();
                return popup;
            }
            else return nullptr;
			
        case 3: //Shop Info
            if (popups[id]) {
                auto popup = UICustom::Popup::createAsMessage("GROSSVATER",
                                      "Hier kannst du alles kaufen was du für die Bienen brauchst.\n"
                                      "Ziehe dazu einfach was du kaufen willst auf die Karte.");
                popups[id] = false;
                SaveLoad::saveStory();
                return popup;
            }
            return nullptr;
			
        case 4: //Fall/Winter Season Info
            if (popups[id]) {
                auto popup = UICustom::Popup::createAsMessage("GROSSVATER",
                                      "Der Winter naht.\n"
                                      "Die Bienen brauchen genug Nahrung um den Winter zu überleben.");
                popups[id] = false;
                SaveLoad::saveStory();
                return popup;
            }
            return nullptr;

	    case 5: // Beehive dead
            if (popups[id]) {
                auto popup = UICustom::Popup::createAsMessage("GROSSVATER",
                                                              "Oh nein...\n"
                                                              "Ein Bienenvolk ist gestorben!\n"
                                                              "Eventuell kannst du es neu bevölkern.");
                popups[id] = false;
                SaveLoad::saveStory();
                return popup;
	        }
	        return nullptr;

        default:
            return nullptr;
    }
}

void StoryScene::toJSON(rapidjson::Document &doc) {
    rapidjson::Value obj(rapidjson::kObjectType);

    for (auto i = 0; i < popups.size(); i++) {
        const char s[] = {'p', 'o', 'p', 'o', 'p', static_cast<const char>(i)};
        obj.AddMember(s, popups[i], doc.GetAllocator());
    }
    doc.PushBack(obj, doc.GetAllocator());
}

void StoryScene::fromJSON(rapidjson::Document &doc) {
    assert(doc.IsArray());
    const rapidjson::Value &story = doc[0];
    for (auto i = 0; i < popups.size(); i++) {
	    const char s[] = {'p', 'o', 'p', 'o', 'p', static_cast<const char>(i)};
        assert(story[s].IsBool());
        popups[i] = story[s].GetBool();
    }
}

 void StoryScene::setTutorial(bool value){
    for (auto && popup : popups) {
        popup = value;
    }
    SaveLoad::saveStory();
}

StoryScene::StoryScene() {
    for (int i = 0; i < 5; i++) popups.push_back(true); // all tutorials. Need to increase counter in case of new one
}
