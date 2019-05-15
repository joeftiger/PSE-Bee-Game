
#include <Resources/Tiles.h>
#include <TileMapObjects/PlaceableTile.h>
#include <Resources/Sprites.h>
#include <TileMapObjects/PlaceableSprite.h>
#include <Resources/SpriteContainer.h>
#include <cocos/ui/UIButton.h>
#include "ItemPanelLayer.h"
#include "TouchUtil.h"
#include "HeaderFiles/DEFINITIONS.h"
#include "MainMenu/MainMenuScene.h"
#include "Game/TileMapLayer.h"
#include "Game/Wallet.h"
#include "Game/Prices.h"
#include "Story/StoryScene.h"
#include "Game/GameScene.h"

using namespace cocos2d;

LayerColor *ItemPanelLayer::createLayer() { return ItemPanelLayer::create(); }

bool ItemPanelLayer::init() {

	if (!LayerColor::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getWinSize();

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(ItemPanelLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(ItemPanelLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(ItemPanelLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//Item Panel
	this->setColor(Color3B::WHITE);
	this->setContentSize(Size(visibleSize.width / 4, visibleSize.height));
	this->setPosition(visibleSize.width, 0);
	this->setOpacity(GLubyte(90));

	//show Item Panel Layer
    auto showButton = ui::Button::create("shop/shop_1.png");

    showButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED){
            // Tutorial
            auto storyScene = StoryScene::getInstance();
            UICustom::Popup* popup = storyScene->createPopup(3);
            if (popup){
                auto scene = (GameScene*) Director::getInstance()->getRunningScene();
                scene->getCameraContainer()->addChild(popup,200);
            }

		    this->showHideItemPanel();
            // create Intro popup

		}
    });

    //showButton = SpriteContainer::getInstance()->getSpriteOf(Sprites::SpriteID::shop_1);
	showButton->setAnchorPoint(Vec2(1, 0.5));
	showButton->setPosition(Vec2(0, this->getContentSize().height / 2));
	showButton->setScale(0.6f);
	this->addChild(showButton);

    //shop background
    auto bg = Sprite::create("shop/shop-bg_neu.png");
    bg->setScale(this->getContentSize().width/bg->getContentSize().width);
    bg->setAnchorPoint(Vec2(1,1));
    bg->setPosition(this->_contentSize);
    //this->addChild(bg);

	initializeItemPanel();

	return true;
}

void ItemPanelLayer::initializeItemPanel() {
	auto box = this->getBoundingBox().size;

	//create label configuration, can be reused in all labels
	TTFConfig labelConfig;
	labelConfig.fontFilePath = FONT;
	labelConfig.fontSize = TEXT_SIZE_HUD;

    _placeables.emplace_back(new PlaceableTile(Tiles::beehive_small));
	_placeables.emplace_back(new PlaceableTile(Tiles::beehive_middle));
	_placeables.emplace_back(new PlaceableTile(Tiles::beehive_big));
	_placeables.emplace_back(new PlaceableTile(Tiles::flower_blue_big));
	_placeables.emplace_back(new PlaceableTile(Tiles::flower_white_big));
	_placeables.emplace_back(new PlaceableTile(Tiles::flower_red_big));
	_placeables.emplace_back(new PlaceableTile(Tiles::flower_pink_big));
	_placeables.emplace_back(new PlaceableTile(Tiles::bush_big));
	_placeables.emplace_back(new PlaceableTile(Tiles::road));
	_placeables.emplace_back(new PlaceableSprite(Sprites::tree_1_spring_summer));
	_placeables.emplace_back(new PlaceableSprite(Sprites::tree_2_spring_summer));
	_placeables.emplace_back(new PlaceableSprite(Sprites::tree_3_spring_summer_fall));

	auto width = 0;
	auto height = 0;
	for (auto p : _placeables) {
		auto x = (width % 3) * box.width / 3;
		auto y = (4 - (height % 4)) * box.height / 6;
		auto pos = Vec2(x, y);

		auto sprite = p->getSprite(); 
		sprite->setPosition(pos);
		sprite->setAnchorPoint(Vec2(0.0f, 0.0f));
		sprite->setScale(box.width / (sprite->getBoundingBox().size.width * 3));
		this->addChild(sprite, x + y);

		
		auto price = Label::createWithTTF(labelConfig, std::to_string(p->getPrice())); //TODO: Change Text to p->getPrice() once implemented
		price->enableOutline(Color4B::BLACK, 1);
		price->setAnchorPoint(Vec2(0.5f, 1.0f));
		price->setPositionX(pos.x + sprite->getBoundingBox().size.width * 0.5f); //TODO:fix Position
		price->setPositionY(pos.y);
		this->addChild(price, sprite->getLocalZOrder() + 1);

		auto priceSprite = SpriteContainer::getInstance()->getSpriteOf(Sprites::coin_single);
		priceSprite->setScale(0.3f);
		priceSprite->setAnchorPoint(Vec2(1.0f, 0.5f));
		priceSprite->setPositionX(-priceSprite->getBoundingBox().size.width * 3 / 5); //TODO:fix Position
		priceSprite->setPositionY(priceSprite->getBoundingBox().size.height / 1.5f);
		price->addChild(priceSprite, sprite->getLocalZOrder() + 1);

		_spritesToPlaceables.emplace(sprite, p);

		width++;
		if (width % 3 == 0) height++;
	}
}

void ItemPanelLayer::setTileMap(TileMapLayer* tileMap) {
    _tileMapLayer = tileMap;
}

void ItemPanelLayer::showHideItemPanel() {
		if (_isItemShow) {
			MoveBy *hide = MoveBy::create(0.2, Vec2(this->getBoundingBox().size.width, 0));
			this->runAction(hide);
			_isItemShow = false;

			_tileMapLayer->showObstructions(false);
		} else {
			MoveBy *show = MoveBy::create(0.2, Vec2(-this->getBoundingBox().size.width, 0));
			this->runAction(show);
			_isItemShow = true;

			_tileMapLayer->showObstructions(true);
		}

}

void ItemPanelLayer::touchOnItemPanel(const Vec2 &touchPos) {
	if (this->getBoundingBox().containsPoint(touchPos)) {
		this->setDrag(touchPos - this->getPosition());
		if (isDrag()) {
			this->addChild(_draggedSprite);
		}
		_isTouch = true;
	}
}

bool ItemPanelLayer::onTouchBegan(Touch *touch, Event *event) {
    if (_isItemShow) {
        touchOnItemPanel(touch->getLocation());
    }
    return _isTouch;
}

void ItemPanelLayer::onTouchMoved(Touch *touch, Event *event) {
    if (isDrag()) {
        _draggedSprite->setPosition(touch->getLocation() - this->getPosition());
    }
}

void ItemPanelLayer::onTouchEnded(Touch *touch, void *) {
    auto pos = touch->getLocation() + this->getParent()->getPosition();
    if (isDrag()) {
    	if (_tileMapLayer->canPlace(_draggedPlaceable, pos)) {
			if (Wallet::getInstance()->subtractMoney(_draggedPlaceable->getPrice())) { //TODO: actual price
				_tileMapLayer->place(_draggedPlaceable, pos);
			}
    	}

        this->removeChild(this->getDraggedSprite());
        this->setIsDrag(false);
    }
    _isTouch = false;
}