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
    parent->addToSpriteList("sprites/blumen1_spring_summer.png", Vec2(0 + 10, 0), flower);
    parent->addToSpriteList("sprites/busch1_spring_summer.png", Vec2(this->getContentSize().width/3 + 10, this->getContentSize().height/7), bush1);
    parent->addToSpriteList("sprites/busch2_spring_summer.png", Vec2(0 + 10, this->getContentSize().height*2/7), bush2);
    parent->addToSpriteList("sprites/busch3_spring_summer.png", Vec2(this->getContentSize().width/3 + 10, this->getContentSize().height*3/7), bush3);
    parent->addToSpriteList("sprites/busch4_spring_summer.png", Vec2(0 + 10, this->getContentSize().height*4/7), bush4);
    parent->addToSpriteList("sprites/steinplattenboden.png", Vec2(this->getContentSize().width/3 + 10, this->getContentSize().height*5/7), road);
}

LayerColor* ItemPanelLayer::getShowRec() {
    return _showRec;
}