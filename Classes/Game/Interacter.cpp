//
// Created by Tobias on 27.04.2019.
//
#include "Interacter.h"

bool Interacter::init() {
    if(!Node::init()) return false;

    return true;
}

void Interacter::runWith(Interactable *interactingObj) {
    this->interactingObj = interactingObj;
}

/**
	Interact with the initialized object
*/
void Interacter::interact() {
	assert(interactingObj);
	InteractionNode* node = InteractionNode::create();
	node->setFiles(interactingObj->getSprite());
	GameScene* scene = (GameScene*)Director::getInstance()->getRunningScene();
	scene->getCameraContainer()->addChild(node);
	node->runAnimation();

    interactingObj->doTask();
}





