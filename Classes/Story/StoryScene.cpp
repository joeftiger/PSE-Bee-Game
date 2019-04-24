

#include "StoryScene.h"
#include "Popup.h"


Scene *StoryScene::createScene() { 	return StoryScene::create(); }

bool StoryScene::init() {

	if (!Scene::init()) {
		return false;

	}

    UICustom::Popup *popup = UICustom::Popup::createAsMessage("Test 2", "This is a Message Popup");
    this->addChild(popup);

	return true;
}
