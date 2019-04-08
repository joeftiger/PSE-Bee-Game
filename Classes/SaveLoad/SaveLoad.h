#ifndef SAVELOAD_H
#define SAVELOAD_H


#include "cocos2d.h"
#include "Game/TileMapLayer.h"
#include "Game/BeeHive.h"
#include "json/rapidjson.h"
#include "json/document.h"


using namespace cocos2d;

class SaveLoad {
private:
public:

	SaveLoad();

	static void saveMap(TMXTiledMap *map);

	static void loadMap();

	static bool fileExists(std::string filename);

	static std::string getPath(std::string fileName);

	static void jsonToFile(std::string, std::string fullpath);

	static void jsonToFile(rapidjson::Document &jsonObj, std::string fullPath);

	static std::string jsonToString(rapidjson::Document &jsonObj);

	static void saveBeehives(std::vector <BeeHive> BeeHives);

	static void loadBeehives();

};

#endif //SAVELOAD_H