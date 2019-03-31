//
// Created by Uro on 3/30/2019.
//

#include "ItemPanelLayer.h"
#include "TouchUtil.h"
#include "HeaderFiles/DEFINITIONS.h"
#include "MainMenu/MainMenuScene.h"

using namespace cocos2d;

LayerColor *ItemPanelLayer::createLayer()
{
    return ItemPanelLayer::create();
}

bool ItemPanelLayer::init() {

    if ( !LayerColor::init() )
    {
        return false;
    }
    Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    auto visibleSize = visibleRect.size;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Item Panel, may want to make his own layer class
    this->setColor(Color3B::WHITE);
    this->setContentSize(Size(visibleSize.width/4, visibleSize.height));
    this->setPosition(visibleSize.width, 0);
    this->setOpacity(GLubyte(90));

    //show Item Panel Layer
    _showRec = LayerColor::create(Color4B::WHITE, 20, 40);
    _showRec->setPosition(0 - 20, this->getContentSize().height/2 - 20);
    this->addChild(_showRec);

    return true;
}

void ItemPanelLayer::initializeItemPanel(TouchUtil *parent) {
    auto box = this->getBoundingBox().size;

    parent->addToSpriteList("tilemaps/Tiles/blumen1_spring_summer.png", Vec2(0, box.height/6), flower1, box);
    parent->addToSpriteList("tilemaps/Tiles/blumen2_spring_summer.png", Vec2(box.width/3, box.height/6), flower2, box);
    parent->addToSpriteList("tilemaps/Tiles/blumen3_spring_summer.png", Vec2(box.width*2/3, box.height/6), flower3, box);
    parent->addToSpriteList("tilemaps/Tiles/blumen4_spring_summer.png", Vec2(0, box.height*2/6), flower4, box);

    parent->addToSpriteList("tilemaps/Tiles/steinplattenboden.png", Vec2(box.width/3, box.height*2/6), road, box);
    parent->addToSpriteList("tilemaps/Tiles/busch1_spring_summer.png", Vec2(box.width*2/3, box.height*2/6), bush1, box);
    parent->addToSpriteList("tilemaps/Tiles/busch2_spring_summer.png", Vec2(0, box.height*3/6), bush2, box);
    parent->addToSpriteList("tilemaps/Tiles/busch3_spring_summer.png", Vec2(box.width/3, box.height*3/6), bush3, box);
    parent->addToSpriteList("tilemaps/Tiles/busch4_spring_summer.png", Vec2(box.width*2/3, box.height*3/6), bush4, box);

    parent->addToSpriteList("tilemaps/Tiles/bienenstock1_gross.png", Vec2(0, box.height*4/6), beehiveBig, box);
    parent->addToSpriteList("tilemaps/Tiles/bienenstock1_mittel.png", Vec2(box.width/3, box.height*4/6), beehiveMiddle, box);
    parent->addToSpriteList("tilemaps/Tiles/bienenstock1_klein.png", Vec2(box.width*2/3, box.height*4/6), beehiveSmall, box);
}

LayerColor* ItemPanelLayer::getShowRec() {
    return _showRec;
}