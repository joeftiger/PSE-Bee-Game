
#include "Interacter.h"
#include "GameScene.h"

bool Interacter::init() {
    if(!Node::init()) return false;

    return true;
}

void Interacter::runWith(Interactable *interactingObj) {
    this->interactingObj = interactingObj;
}

void Interacter::interact() {
	assert(interactingObj);
	InteractionNode* node = InteractionNode::create();
	node->setFiles(interactingObj->getSprite());
	GameScene* scene = (GameScene*)Director::getInstance()->getRunningScene();
	scene->getCameraContainer()->addChild(node);
	node->runAnimation();

    interactingObj->doTask();
}





