

#include "StoryScene.h"
#include "Popup.h"


Scene *StoryScene::createScene() { 	return StoryScene::create(); }

bool StoryScene::init() {

	if (!Scene::init()) {
		return false;

	}



	UICustom::Popup *popup = UICustom::Popup::createAsMessage("GROSSVATER", "Hallo mein Enkel, schön bist du da. Ich hätte eine bitte an dich...");
	this->addChild(popup);




	return true;
}
