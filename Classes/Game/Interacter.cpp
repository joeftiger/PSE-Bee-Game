//
// Created by Tobias on 27.04.2019.
//
#include "Interacter.h"

bool Interacter::init() {
    if(!Node::init()) return false;

    //TODO: add Interface with buttons

    return true;
}

void Interacter::runWith(Interactable *interactingObj) {
    this->interactingObj = interactingObj;
}

void Interacter::interact() {
    interactingObj->doTask();
}





