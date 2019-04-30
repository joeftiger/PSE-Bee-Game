//
// Created by julius on 28.04.19.
//

#include "SpriteContainer.h"

SpriteContainer::SpriteContainer() {
    std::string path = "tilemaps/Tiles/SD/";

    _GIDsprites.emplace(Tiles::beehiveBig1    , Sprite::create(path + "bienenstock1_gross.png"));
    _GIDsprites.emplace(Tiles::beehiveSmall1  , Sprite::create(path + "bienenstock1_klein.png"));
    _GIDsprites.emplace(Tiles::beehiveMiddle1 , Sprite::create(path + "bienenstock1_mittel.png"));
    _GIDsprites.emplace(Tiles::beehiveBig2    , Sprite::create(path + "bienenstock2_gross.png"));
    _GIDsprites.emplace(Tiles::beehiveSmall2  , Sprite::create(path + "bienenstock2_klein.png"));
    _GIDsprites.emplace(Tiles::beehiveMiddle2 , Sprite::create(path + "bienenstock2_mittel.png"));
    _GIDsprites.emplace(Tiles::beehiveBig3    , Sprite::create(path + "bienenstock3_gross.png"));
    _GIDsprites.emplace(Tiles::beehiveMiddle3 , Sprite::create(path + "bienenstock3_mittel.png"));
    _GIDsprites.emplace(Tiles::flower1        , Sprite::create(path + "blumen1_spring_summer.png"));
    _GIDsprites.emplace(Tiles::flower2        , Sprite::create(path + "blumen2_spring_summer.png"));
    _GIDsprites.emplace(Tiles::flower3        , Sprite::create(path + "blumen3_spring_summer.png"));
    _GIDsprites.emplace(Tiles::flower4        , Sprite::create(path + "blumen4_spring_summer.png"));
    _GIDsprites.emplace(Tiles::bush1          , Sprite::create(path + "busch1_spring_summer.png"));
    _GIDsprites.emplace(Tiles::bush2          , Sprite::create(path + "busch2_spring_summer.png"));
    _GIDsprites.emplace(Tiles::bush3          , Sprite::create(path + "busch3_spring_summer.png"));
    _GIDsprites.emplace(Tiles::bush4          , Sprite::create(path + "busch4_spring_summer.png"));
    _GIDsprites.emplace(Tiles::grass          , Sprite::create(path + "grasflàche.png"));
    _GIDsprites.emplace(Tiles::road           , Sprite::create(path + "steinplattenboden.png"));
    // these are currently only in the spritesheetSD.png
    _GIDsprites.emplace(Tiles::obstruction    , nullptr);
    _GIDsprites.emplace(Tiles::no_obstruction , nullptr);

    path = "tilemaps/Sprites/";
    _IDsprites.emplace(Sprites::tree_1        , Sprite::create(path + "baum1_spring_summer.png"));
    _IDsprites.emplace(Sprites::tree_1_apple_1, Sprite::create(path + "baum1_apfel1.png"));
    _IDsprites.emplace(Sprites::tree_1_apple_2, Sprite::create(path + "baum1_apfel2.png"));
    _IDsprites.emplace(Sprites::tree_1_apple_3, Sprite::create(path + "baum1_apfel3.png"));
    _IDsprites.emplace(Sprites::tree_2        , Sprite::create(path + "baum2_spring_summer.png"));
    _IDsprites.emplace(Sprites::tree_2_apple_1, Sprite::create(path + "baum2_apfel1.png"));
    _IDsprites.emplace(Sprites::tree_2_apple_2, Sprite::create(path + "baum2_apfel2.png"));
    _IDsprites.emplace(Sprites::tree_2_apple_3, Sprite::create(path + "baum2_apfel3.png"));
    _IDsprites.emplace(Sprites::tree_3_summer , Sprite::create(path + "baum3_spring_summer.png"));
    _IDsprites.emplace(Sprites::tree_3_winter , Sprite::create(path + "baum3_winter.png"));
    _IDsprites.emplace(Sprites::tree_4        , Sprite::create(path + "baum4_spring_summer.png"));
    _IDsprites.emplace(Sprites::tree_4_apple_1, Sprite::create(path + "baum4_apfel1.png"));
    _IDsprites.emplace(Sprites::tree_4_apple_2, Sprite::create(path + "baum4_apfel2.png"));
    _IDsprites.emplace(Sprites::tree_4_apple_3, Sprite::create(path + "baum4_apfel3.png"));
    _IDsprites.emplace(Sprites::erlenmeyer    , Sprite::create(path + "erlenmeyerkolben.png"));
    _IDsprites.emplace(Sprites::honey_glass_2d, Sprite::create(path + "honigglas_2d.png"));
    _IDsprites.emplace(Sprites::honey_glass_3d, Sprite::create(path + "honigglas_3d.png"));
    _IDsprites.emplace(Sprites::honey_bucket  , Sprite::create(path + "honigkessel.png"));
    _IDsprites.emplace(Sprites::honey_extractor,Sprite::create(path + "honigschleuder.png"));
    _IDsprites.emplace(Sprites::coin_single   , Sprite::create(path + "münze_einzeln.png"));
    _IDsprites.emplace(Sprites::coin_pile     , Sprite::create(path + "münze_haufen.png"));
}

Sprite *SpriteContainer::getSpriteOf(Tiles::TileGID gid) {
    return _GIDsprites.at(gid);
}

Sprite *SpriteContainer::getSpriteOf(Sprites::SpriteID id) {
    return _IDsprites.at(id);
}
