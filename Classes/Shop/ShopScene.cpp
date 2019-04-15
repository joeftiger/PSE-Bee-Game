
#include "ShopScene.h"
#include <cocos2d.h>
#include <cocos/ui/UIScrollView.h>
#include <cocos/ui/UIButton.h>

using namespace cocos2d;

Scene *ShopScene::createScene() {
	return ShopScene::create();
}


bool ShopScene::init(){
    if ( !Scene::init()) return false;

    cocos2d::Rect visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //create ScrollView for Shop Items
    auto *shopView = ui::ScrollView::create();
    shopView->setDirection(ui::ScrollView::Direction::VERTICAL);
    shopView->setContentSize( visibleRect.size);
    shopView->setInnerContainerSize( Size(400, 500));
    shopView->setBackGroundImage("shop/shop-bg.png");
    shopView->setBounceEnabled( true );
    shopView->setAnchorPoint( Vec2(0.5, 0.5));
    shopView->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    //initialize buttons
    auto *button1 = MenuItemImage::create("menu/play-button.png", "menu/play-button.png");
    auto *button2 = MenuItemImage::create("menu/options-button.png", "menu/options-button.png");
    auto *button3 = MenuItemImage::create("menu/about-button.png", "menu/about-button.png");
    button3->setPosition(Vec2(shopView->getContentSize().width / 2, 300));

    //initialize sprites
    auto *sprite1 = MenuItemImage::create("sprites/honigglas_2d.png", "sprites/honigglas_2d.png");
    sprite1->setScale(0.1f);
    auto *sprite2 = MenuItemImage::create("sprites/honigglas_2d.png", "sprites/honigglas_2d.png");
    sprite2->setScale(0.1f);
    auto *sprite3 = MenuItemImage::create("sprites/honigglas_2d.png", "sprites/honigglas_2d.png");
    sprite3->setScale(0.1f);

    // adding item rows to the ScrollView

    Vector < MenuItem * > Honey;
    auto *spriteHoney = MenuItemImage::create("sprites/honigglas_2d.png", "sprites/honigglas_2d.png");
    spriteHoney->setScale(0.1f);
    auto *buyHoney = MenuItemImage::create("shop/plus.png", "shop/plus.png");
    auto *sellHoney = MenuItemImage::create("shop/minus.png", "shop/minus.png");
    Honey.pushBack(spriteHoney);
    Honey.pushBack(buyHoney);
    Honey.pushBack(sellHoney);

    auto itemHoney = Menu::createWithArray(Honey);
    itemHoney->alignItemsHorizontallyWithPadding(100);
    itemHoney->setPosition(Vec2(shopView->getContentSize().width / 2, 100));
    itemHoney->setContentSize(Size(visibleSize.width, 100));
    shopView->addChild(itemHoney);

    Vector < MenuItem * > MenuItems2;
    MenuItems2.pushBack(sprite2);
    MenuItems2.pushBack(button2);
    auto itemMenu2 = Menu::createWithArray(MenuItems2);
    itemMenu2->alignItemsHorizontallyWithPadding(100);
    itemMenu2->setPosition(Vec2(shopView->getContentSize().width / 2, 200));
    itemMenu2->setContentSize(Size(visibleSize.width, 200));
    shopView->addChild(itemMenu2);

    this->addChild(shopView);

    // create Layout
    /*
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
    */

    return true;
}
