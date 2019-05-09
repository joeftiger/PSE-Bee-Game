
#ifndef PROJ_ANDROID_INTERACTER_H
#define PROJ_ANDROID_INTERACTER_H

#include "cocos2d.h"
#include "../HeaderFiles/Interactable.h"
#include "Interaction/InteractionNode.h"

using namespace cocos2d;

/**
 * Creates a new honey extractor with 0 raw honey as input.
 */
class Interacter : public cocos2d::Node {

private:

    Interactable *interactingObj;

public:

    virtual bool init() override;

    void runWith(Interactable *interactingObj);

	/**
     *	Interact with the initialized object
     */
    void interact();

    CREATE_FUNC(Interacter);
};


#endif //PROJ_ANDROID_INTERACTER_H
