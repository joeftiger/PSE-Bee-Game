//
// Created by julius on 28.04.19.
//

#include "SpriteContainer.h"

Sprite *SpriteContainer::getSpriteOf(Tiles::TileGID gid) {
    std::string path = "tilemaps/Tiles/SD/";
    switch (gid) {
        case Tiles::beehiveBig1:    return Sprite::create(path + "bienenstock1_gross.png");
        case Tiles::beehiveSmall1:  return Sprite::create(path + "bienenstock1_klein.png");
        case Tiles::beehiveMiddle1: return Sprite::create(path + "bienenstock1_mittel.png");
        case Tiles::beehiveBig2:    return Sprite::create(path + "bienenstock2_gross.png");
        case Tiles::beehiveSmall2:  return Sprite::create(path + "bienenstock2_klein.png");
        case Tiles::beehiveMiddle2: return Sprite::create(path + "bienenstock2_mittel.png");
        case Tiles::beehiveBig3:    return Sprite::create(path + "bienenstock3_gross.png");
        case Tiles::beehiveMiddle3: return Sprite::create(path + "bienenstock3_mittel.png");
        case Tiles::flower1:        return Sprite::create(path + "blumen1_spring_summer.png");
        case Tiles::flower2:        return Sprite::create(path + "blumen2_spring_summer.png");
        case Tiles::flower3:        return Sprite::create(path + "blumen3_spring_summer.png");
        case Tiles::flower4:        return Sprite::create(path + "blumen4_spring_summer.png");
        case Tiles::bush1:          return Sprite::create(path + "busch1_spring_summer.png");
        case Tiles::bush2:          return Sprite::create(path + "busch2_spring_summer.png");
        case Tiles::bush3:          return Sprite::create(path + "busch3_spring_summer.png");
        case Tiles::bush4:          return Sprite::create(path + "busch4_spring_summer.png");
        case Tiles::grass:          return Sprite::create(path + "grasflàche.png");
        case Tiles::road:           return Sprite::create(path + "steinplattenboden.png");
        case Tiles::obstruction:    return nullptr;
        case Tiles::no_obstruction: return nullptr;
        default:                    return nullptr;
    }
}

Sprite *SpriteContainer::getSpriteOf(Sprites::SpriteID id) {
    std::string path = "tilemaps/Sprites/";
    switch (id) {
        case Sprites::tree_1:           return Sprite::create(path + "baum1_spring_summer.png");
        case Sprites::tree_1_apple_1:   return Sprite::create(path + "baum1_apfel1.png");
        case Sprites::tree_1_apple_2:   return Sprite::create(path + "baum1_apfel2.png");
        case Sprites::tree_1_apple_3:   return Sprite::create(path + "baum1_apfel3.png");
        case Sprites::tree_2:           return Sprite::create(path + "baum2_spring_summer.png");
        case Sprites::tree_2_apple_1:   return Sprite::create(path + "baum2_apfel1.png");
        case Sprites::tree_2_apple_2:   return Sprite::create(path + "baum2_apfel2.png");
        case Sprites::tree_2_apple_3:   return Sprite::create(path + "baum2_apfel3.png");
        case Sprites::tree_3_summer:    return Sprite::create(path + "baum3_spring_summer.png");
        case Sprites::tree_3_winter:    return Sprite::create(path + "baum3_winter.png");
        case Sprites::tree_4:           return Sprite::create(path + "baum4_spring_summer.png");
        case Sprites::tree_4_apple_1:   return Sprite::create(path + "baum4_apfel1.png");
        case Sprites::tree_4_apple_2:   return Sprite::create(path + "baum4_apfel2.png");
        case Sprites::tree_4_apple_3:   return Sprite::create(path + "baum4_apfel3.png");
        case Sprites::erlenmeyer:       return Sprite::create(path + "erlenmeyerkolben.png");
        case Sprites::honey_glass_2d:   return Sprite::create(path + "honigglas_2d.png");
        case Sprites::honey_glass_3d:   return Sprite::create(path + "honigglas_3d.png");
        case Sprites::honey_bucket:     return Sprite::create(path + "honigkessel.png");
        case Sprites::honey_extractor:  return Sprite::create(path + "honigschleuder.png");
        case Sprites::coin_single:      return Sprite::create(path + "münze_einzeln.png");
        case Sprites::coin_pile:        return Sprite::create(path + "münze_haufen.png");
        default:                        return nullptr;
    }
}
