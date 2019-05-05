//
// Created by julius on 28.04.19.
//

#include <Settings.h>
#include "SpriteContainer.h"


SpriteContainer::SpriteContainer() {
    cocos2d::log("SpriteContainer:\tCreating Instance");
    loadSpriteSheet();
}

void SpriteContainer::loadSpriteSheet() {
    if (Settings::getInstance()->getAsBool(Settings::HD_Textures)) {
        _cache->removeSpriteFramesFromFile("Spritesheet/SD/spritesheet.plist");
        _cache->removeSpriteFramesFromFile("Spritesheet/SD/tilesheet.plist");
        _cache->addSpriteFramesWithFile("Spritesheet/HD/spritesheet.plist");
        _cache->addSpriteFramesWithFile("Spritesheet/HD/tilesheet.plist");
    } else {
        _cache->removeSpriteFramesFromFile("Spritesheet/HD/spritesheet.plist");
        _cache->removeSpriteFramesFromFile("Spritesheet/HD/tilesheet.plist");
        _cache->addSpriteFramesWithFile("Spritesheet/SD/spritesheet.plist");
        _cache->addSpriteFramesWithFile("Spritesheet/SD/tilesheet.plist");
    }
}

Sprite *SpriteContainer::getSpriteOf(Tiles::TileGID gid) {
    switch (gid) {
        case Tiles::beehive_small:              return Sprite::createWithSpriteFrameName("1_1_bienenstock1_klein.png");
        case Tiles::beehive_middle:             return Sprite::createWithSpriteFrameName("1_2_bienenstock1_mittel.png");
        case Tiles::beehive_big:                return Sprite::createWithSpriteFrameName("1_3_bienenstock1_gross.png");
        case Tiles::beehive_small_open:         return Sprite::createWithSpriteFrameName("1_4_bienenstock2_klein.png");
        case Tiles::beehive_middle_open:        return Sprite::createWithSpriteFrameName("1_5_bienenstock2_mittel.png");
        case Tiles::beehive_big_open:           return Sprite::createWithSpriteFrameName("1_6_bienenstock2_gross.png");
        case Tiles::beehive_middle_overflow:    return Sprite::createWithSpriteFrameName("1_7_bienenstock3_mittel.png");
        case Tiles::beehive_big_overflow:       return Sprite::createWithSpriteFrameName("1_8_bienenstock3_gross.png");
        case Tiles::grass:                      return Sprite::createWithSpriteFrameName("1_9_grasflaeche.png");
        case Tiles::road:                       return Sprite::createWithSpriteFrameName("1_10_steinplattenboden.png");
        case Tiles::beehive_small_winter:       return Sprite::createWithSpriteFrameName("2_1_bienenstock_klein_winter.png");
        case Tiles::beehive_middle_winter:      return Sprite::createWithSpriteFrameName("2_2_bienenstock_mittel.png");
        case Tiles::beehive_big_winter:         return Sprite::createWithSpriteFrameName("2_3_bienenstock_gross_winter.png");
        case Tiles::flower_blue_small:          return Sprite::createWithSpriteFrameName("2_4_blumen1.3.png");
        case Tiles::flower_blue_middle:         return Sprite::createWithSpriteFrameName("2_5_blumen1.2.png");
        case Tiles::flower_blue_big:            return Sprite::createWithSpriteFrameName("2_6_blumen1.png");
        case Tiles::flower_red_small:           return Sprite::createWithSpriteFrameName("2_7_blumen2.3.png");
        case Tiles::flower_red_middle:          return Sprite::createWithSpriteFrameName("2_8_blumen2.2.png");
        case Tiles::flower_red_big:             return Sprite::createWithSpriteFrameName("2_9_blumen2.png");
        case Tiles::snow:                       return Sprite::createWithSpriteFrameName("2_10_schneetextur.png");
        case Tiles::brushwood_small:            return Sprite::createWithSpriteFrameName("3_1_busch1_spring_summer_fall.png");
        case Tiles::bush_small:                 return Sprite::createWithSpriteFrameName("3_2_busch2_spring_summer_fall.png");
        case Tiles::bush_big:                   return Sprite::createWithSpriteFrameName("3_3_busch3_spring_summer_fall.png");
        case Tiles::brushwood_big:              return Sprite::createWithSpriteFrameName("3_4_busch4_spring_summer_fall.png");
        case Tiles::flower_white_small:         return Sprite::createWithSpriteFrameName("3_5_blumen3.3.png");
        case Tiles::flower_white_middle:        return Sprite::createWithSpriteFrameName("3_6_blumen3.2.png");
        case Tiles::flower_white_big:           return Sprite::createWithSpriteFrameName("3_7_blumen3.png");
        case Tiles::flower_pink_small:          return Sprite::createWithSpriteFrameName("3_8_blumen4.3.png");
        case Tiles::flower_pink_middle:         return Sprite::createWithSpriteFrameName("3_9_blumen4.2.png");
        case Tiles::flower_pink_big:            return Sprite::createWithSpriteFrameName("3_10_blumen4.png");
        case Tiles::brushwood_small_winter:     return Sprite::createWithSpriteFrameName("4_1_busch1_winter.png");
        case Tiles::bush_small_winter:          return Sprite::createWithSpriteFrameName("4_2_busch2_winter.png");
        case Tiles::bush_big_winter:            return Sprite::createWithSpriteFrameName("4_3_busch3_winter.png");
        case Tiles::brushwood_big_winter:       return Sprite::createWithSpriteFrameName("4_4_busch4_winter.png");
        case Tiles::snow_1:                     return Sprite::createWithSpriteFrameName("4_5_schneetextur_rand1.png");
        case Tiles::snow_2:                     return Sprite::createWithSpriteFrameName("4_6_schneetextur_rand2.png");
        case Tiles::snow_3:                     return Sprite::createWithSpriteFrameName("schneetextur_rand3.png");
        case Tiles::snow_4:                     return Sprite::createWithSpriteFrameName("schneetextur_rand4.png");
        case Tiles::obstruction:                return Sprite::createWithSpriteFrameName("4_9_obstruction.png");
        case Tiles::no_obstruction:             return Sprite::createWithSpriteFrameName("4_10_no_obstruction.png");
        default:                                return nullptr;
    }
}

Sprite *SpriteContainer::getSpriteOf(Sprites::SpriteID id) {
    SpriteFrame *frame;
    switch (id) {
        case Sprites::tree_1_spring_summer:         return Sprite::createWithSpriteFrameName("baum1_spring_summer.png");
        case Sprites::tree_1_fall:                  return Sprite::createWithSpriteFrameName("baum1_fall.png");
        case Sprites::tree_1_winter:                return Sprite::createWithSpriteFrameName("baum1_winter.png");
        case Sprites::tree_1_apple_1:               return Sprite::createWithSpriteFrameName("baum1_apfel1.png");
        case Sprites::tree_1_apple_2:               return Sprite::createWithSpriteFrameName("baum1_apfel2.png");
        case Sprites::tree_1_apple_3:               return Sprite::createWithSpriteFrameName("baum1_apfel3.png");
        case Sprites::tree_2_spring_summer:         return Sprite::createWithSpriteFrameName("baum2_spring_summer.png");
        case Sprites::tree_2_fall:                  return Sprite::createWithSpriteFrameName("baum2_fall.png");
        case Sprites::tree_2_winter:                return Sprite::createWithSpriteFrameName("baum2_winter.png");
        case Sprites::tree_2_apple_1:               return Sprite::createWithSpriteFrameName("baum2_apfel1.png");
        case Sprites::tree_2_apple_2:               return Sprite::createWithSpriteFrameName("baum2_apfel2.png");
        case Sprites::tree_2_apple_3:               return Sprite::createWithSpriteFrameName("baum2_apfel3.png");
        case Sprites::tree_3_spring_summer_fall:    return Sprite::createWithSpriteFrameName("baum3_spring_summer_fall.png");
        case Sprites::tree_3_winter:                return Sprite::createWithSpriteFrameName("baum3_winter.png");
        case Sprites::tree_4_spring_summer:         return Sprite::createWithSpriteFrameName("baum4_spring_summer.png");
        case Sprites::tree_4_fall:                  return Sprite::createWithSpriteFrameName("baum4_fall.png");
        case Sprites::tree_4_winter:                return Sprite::createWithSpriteFrameName("baum4_winter.png");
        case Sprites::tree_4_apple_1:               return Sprite::createWithSpriteFrameName("baum4_apfel1.png");
        case Sprites::tree_4_apple_2:               return Sprite::createWithSpriteFrameName("baum4_apfel2.png");
        case Sprites::tree_4_apple_3:               return Sprite::createWithSpriteFrameName("baum4_apfel3.png");
        case Sprites::start:                        return Sprite::createWithSpriteFrameName("start.png");
        case Sprites::options:                      return Sprite::createWithSpriteFrameName("options.png");
        case Sprites::credits:                      return Sprite::createWithSpriteFrameName("credits.png");
        case Sprites::exit:                         return Sprite::createWithSpriteFrameName("exit.png");
        case Sprites::shop_1:                       return Sprite::createWithSpriteFrameName("shop_1.png");
        case Sprites::shop_2:                       return Sprite::createWithSpriteFrameName("shop_2.png");
        case Sprites::minus:                        return Sprite::createWithSpriteFrameName("minus.png");
        case Sprites::plus:                         return Sprite::createWithSpriteFrameName("plus.png");
        case Sprites::erlenmeyer:                   return Sprite::createWithSpriteFrameName("erlenmeyerkolben.png");
        case Sprites::honey_glass_2d:               return Sprite::createWithSpriteFrameName("honigglas_2d.png");
        case Sprites::honey_glass_3d:               return Sprite::createWithSpriteFrameName("honigglas_3d.png");
        case Sprites::honey_bucket:                 return Sprite::createWithSpriteFrameName("honigkessel.png");
        case Sprites::honey_extractor:              return Sprite::createWithSpriteFrameName("honigschleuder.png");
        case Sprites::coin_single:                  return Sprite::createWithSpriteFrameName("münze_einzeln.png");
        case Sprites::coin_pile:                    return Sprite::createWithSpriteFrameName("münze_haufen.png");
        default:                                    return nullptr;
    }
}