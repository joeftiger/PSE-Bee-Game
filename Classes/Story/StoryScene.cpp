

#include "StoryScene.h"


Scene *StoryScene::createScene() {
	return StoryScene::create();
}

bool StoryScene::init() {

	if (!Scene::init()) {
		return false;
	}


	return true;
}
