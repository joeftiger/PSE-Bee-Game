
#ifndef PSE_BEE_GAME_SHOPSCENE_H
#define PSE_BEE_GAME_SHOPSCENE_H

#include "cocos2d.h"
#include "HeaderFiles/DEFINITIONS.h"


class ShopScene : public cocos2d::Scene {
private:
public:
	static cocos2d::Scene *createScene();

	virtual bool init();




	CREATE_FUNC(ShopScene);

};


#endif //PSE_BEE_GAME_SHOPSCENE_H
