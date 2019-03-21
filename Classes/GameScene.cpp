
#include "GameScene.h"
#include "BeeStock.h"
#include "SimpleAudioEngine.h"
#include "math.h"

Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if ( !Scene::init()) return false;

	cocos2d::Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    _tileMap = TMXTiledMap::create("tilemaps/tilemapHD.tmx");
    _background = _tileMap->getLayer("background");

    this->addChild(_tileMap, -1);
    _tileMap->setAnchorPoint(Point(0.5,0.5));
    _tileMap->setScale(0.5f);


    //add the menu item for back to main menu
    auto label = Label::createWithTTF("Main Menu", "fonts/OpenSans-Regular.ttf", 20);
    auto menuItem = MenuItemLabel::create(label);
    menuItem->setCallback([&](cocos2d::Ref *sender) {
        Director::getInstance()->replaceScene(MainMenu::scene());
    });

    auto backMenu = Menu::create(menuItem, nullptr);
    backMenu->setPosition(Vec2::ZERO);
    backMenu->setPosition(Vec2(visibleRect.origin.x+visibleRect.size.width - 80, visibleRect.origin.y + 25));
	this->addChild(backMenu, 1);



//    _player = Sprite::create("tilemapTobi/TileGameResources/Player.png");
//    this->addChild(_player);
//
//
//
//    //get spawnpoint
//    TMXObjectGroup *objectGroup = _tileMap->getObjectGroup("Objects");
//    if(objectGroup == NULL) {
//        log("tile map has no object layer");
//        return false;
//    }
//
//    ValueMap spawnPoint = objectGroup->getObject("SpawnPoint");
//    float xSpawn = spawnPoint["x"].asFloat();
//    float ySpawn = spawnPoint["y"].asFloat();
//
//    this->setPlayerPosition(Point(xSpawn,ySpawn));
//
//    auto followPlayer = Follow::create(_player);
//    this->runAction(followPlayer);

    return true;
}

void GameScene::setPlayerPosition(Point position) {
    _player->setPosition(position);
}

bool GameScene::onTouchBegan(Touch *touch, Event *event) {
    _isTouched = true;
    _touchPosition = touch->getLocation();

	//auto sprite = static_cast<Sprite*>(event->getCurrentTarget());
	//Point loc = sprite->convertToNodeSpace(_touchPosition);
	
	//Sprite* s = _background->getTileAt(Vec2(1, 1));
	//s->setOpacity(0);
	Point loc = this->convertToNodeSpace(_touchPosition);
	//Rect recTemp = sprite->getBoundingBox();
	//if (recTemp.containsPoint(loc)) {
		log("%f %f",loc.x, loc.y );
		//return true;

	//}
	Point p = GameScene::getClosestTile(_touchPosition);
	auto s = _background->getTileAt(p);
	s->setOpacity(0);

	return true;
}

Point GameScene::getClosestTile(Point touchPos) {
	int x;
	int y;
	float d = 1000000;
	Point tempP;

	for (x = 0; x <= 7; x++) {
		for (y = 0;y <= 7; y++) {
			auto temp = _background->getTileAt(Vec2(x, y));
			auto e = temp->getPosition();
			auto t = touchPos;
			auto spritePos = this->convertToNodeSpace(e);
			
			float dTemp = sqrtf(pow(t.x - spritePos.x, 2) + pow(t.y - spritePos.y, 2));
			if (dTemp < d) {
				tempP = Point(x, y);
				d = dTemp;
			}

		}
	}
	log("%f %f", tempP.x, tempP.y);
	return tempP;

}

void GameScene::onTouchMoved(Touch *touch, Event *event) {
    auto touchPos = touch->getLocation();
    auto movement = touchPos - _touchPosition;
    auto finalPos = _background->getPosition() + movement;

    auto winSize = Director::getInstance()->getVisibleSize();

    float posX, posY;
    _background->getPosition(&posX, &posY);


    _background->setPosition(finalPos);

    this->onTouchBegan(touch, event);
}

void GameScene::onTouchEnded(void *, void *) {
    _isTouched = false;
    _touchPosition = Point(0, 0);
}
