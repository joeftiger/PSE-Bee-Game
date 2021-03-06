
#ifndef SAVEDELETECONFIRMATION_H
#define SAVEDELETECONFIRMATION_H


#include "cocos2d.h"

using namespace cocos2d;
/*
 * scene to ask for an additional confirmation for deleting the save
 */
class SaveDeleteConfirmation : public cocos2d::Scene {
private:

	float onePofScreenH;
	float onePofScreenW;

public:
	static cocos2d::Scene *createScene();

	virtual bool init();

	/**
	 * when clicking on  yes, delete save and go back to main menu
     * Delay: 0.1 seconds       Colour: White
	 */
    void onYesClick(cocos2d::Ref *sender);

    /**
     * when clicking on  no, go back to options scene without deleting save
     * Delay: 0.1 seconds       Colour: White
     */
    void onNoClick(cocos2d::Ref *sender);

	// implement the "static create()" method manually
	CREATE_FUNC(SaveDeleteConfirmation);
};

#endif //SAVEDELETECONFIRMATION_H
