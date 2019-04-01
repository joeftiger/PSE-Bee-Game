
#include "ShopScene.h"
#include <cocos2d.h>
#include <cocos/ui/UILayout.h>
#include <cocos/ui/UIButton.h>

using namespace cocos2d;

Scene* ShopScene::createScene()
{
    return ShopScene::create();
}

bool ShopScene::init(){
    if ( !Scene::init()) return false;

    cocos2d::Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // create Layout
    auto *sprite1 = Sprite::create("sprites/honigglas_2d.png");
    sprite1->setScale(0.1f);
    auto *count1 = TextFieldTTF::create();

    auto *button1 = ui::Button::create("menu/play-button.png");

    auto *button2 = ui::Button::create("menu/options-button.png");
    auto *button3 = ui::Button::create("menu/about-button.png");
    auto *shopLayout = ui::Layout::create(); //Layout for the whole shop
    auto *itemLayout = ui::Layout::create(); //Layout for each row

    shopLayout->setLayoutType(ui::Layout::Type::VERTICAL);
    shopLayout->setPosition(Vec2(300,400));

    itemLayout->setLayoutType(ui::Layout::Type::HORIZONTAL);
    itemLayout->addChild(sprite1);
    itemLayout->addChild(count1);
    itemLayout->addChild(button1);

    shopLayout->addChild(itemLayout);
    shopLayout->addChild(button2);
    shopLayout->addChild(button3);
    this->addChild(shopLayout);


    return true;
}