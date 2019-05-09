
#ifndef _OPTIONSSCENE_H
#define _OPTIONSSCENE_H


#include "cocos2d.h"


using namespace cocos2d;
/**
 * OptionsScene with deleting the save functionality and switching tileMaps
 */
class OptionsScene : public cocos2d::Scene {
private:

	float onePofScreenH;
	float onePofScreenW;



	void initTextureButton();

	void initTutorialButton();

public:
	static cocos2d::Scene *createScene();

	virtual bool init();

	// reset button click handler
	void onDeleteSaveClick(cocos2d::Ref *sender);


	// implement the "static create()" method manually
	CREATE_FUNC(OptionsScene);
};


#endif //_OPTIONSSCENE_H
