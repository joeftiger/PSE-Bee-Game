
#ifndef SHOPSCENE_H
#define SHOPSCENE_H

#include "cocos2d.h"
#include "HeaderFiles/DEFINITIONS.h"

/**
 * shop scene
 * TODO Check if currently used???
 */
class ShopScene : public cocos2d::Scene {
private:
public:
	static cocos2d::Scene *createScene();

	virtual bool init();


	CREATE_FUNC(ShopScene);

};


#endif //SHOPSCENE_H
