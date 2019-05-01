#ifndef SAVELOAD_H
#define SAVELOAD_H


#include "cocos2d.h"

#include "Game/Time.h"
#include "json/rapidjson.h"
#include "json/istreamwrapper.h"
#include "json/ostreamwrapper.h"
#include "json/prettywriter.h"
#include "json/document.h"
#include <json/document.h>
#include <json/stringbuffer.h>
#include <json/writer.h>
#include <iostream>
#include <fstream>

using namespace cocos2d;

class SaveLoad {
private:

	static std::string getPath(std::string fileName);

	static void jsonToFile(std::string, std::string fullpath);

	static void jsonToFile(rapidjson::Document &jsonObj, std::string fullPath);

	static std::string docToString(rapidjson::Document &jsonObj);

public:

	static void saveMap();

	static std::vector<std::vector<int>> loadMap();

	static bool tileMapSaveExists();

	static bool beeHiveSaveExists();

	static bool honeyExtractorSaveExists();

	static bool timesSaveExists();

	static void saveBeehives();

	static void loadBeehives();

	static void saveHoneyExtractors();

    static void loadHoneyExtractors();

	static void saveEverything();

	static void saveTime();

	static void saveMoney();

	static void loadTime();

	static void loadMoney();

	static void deleteTileMapSave();

	static void deleteBeeHivesSave();

	static void deleteHoneyExtractorsSave();

	static void deleteTimeSave();

	static void deleteEverything();
};

#endif //SAVELOAD_H