
#include "StoryScene.h"
#include "Popup.h"
#include "Game/Time.h"

bool StoryScene::init() {

	if (!Node::init()) {
		return false;

	}

	time = Time::getInstance();
	state = true;

	// Popups: Spielstart tutorial, erstes mal varroa,

    this->schedule(schedule_selector(StoryScene::update), 1.0f);


	return true;
}

/*void StoryScene::update(float delta) {
    if (time->getMonth()==4 && state){
        UICustom::Popup *popup = UICustom::Popup::createAsMessage("GROSSVATER", "Hallo mein Enkel, schön bist du da. Ich hätte eine bitte an dich...");
        this->addChild(popup);
        state = false;
    }
}*/

/*void StoryScene::introPopup(){
    UICustom::Popup *popup = UICustom::Popup::createAsMessage("GROSSVATER", "Hallo mein Enkel, schön bist du da. Ich hätte eine bitte an dich...");
    this->addChild(popup);
}*/

UICustom::Popup* StoryScene::createPopup(int id){
	switch (id) {
	case 0: return UICustom::Popup::createAsMessage("GROSSVATER", "Hallo mein Enkel, schön bist du da. Ich hätte eine bitte an dich.\n"
		"Kannst du auf meine Bienen aufpassen? Nur bis ich wieder da bin...");
	case 1: return UICustom::Popup::createAsMessage("GROSSVATER", "Varroa.. iiiiih");
	case 2: return UICustom::Popup::createAsMessage("GROSSVATER", "i");

	}
	/*
    if (id == 0) { //not working
        return UICustom::Popup::createAsMessage("GROSSVATER", "Hallo mein Enkel, schön bist du da. Ich hätte eine bitte an dich...\n"
                                                              "Hallo mein Enkel, schön bist du da. Ich hätte eine bitte an dich...\n"
                                                              "Hallo mein Enkel, schön bist du da. Ich hätte eine bitte an dich...");
    }
    if (id == 1) {
        UICustom::Popup *popup1 = UICustom::Popup::createAsMessage("GROSSVATER",
                                                                   "Varroa.. iiiiih");
        this->addChild(popup1);
    }*/

}