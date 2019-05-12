#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "cocos2d.h"

#include "json/rapidjson.h"
#include "json/document.h"
#include "Game/TileMapLayer.h"

using namespace cocos2d;

/**
 *  all saving, loading and deleting functions via .json files
 */
class SaveLoad {
private:

	static std::string getPath(std::string fileName);

	/**
     *	Returns a writable path for the given filename
     *	@param fileName
     */
	static void jsonToFile(std::string, std::string fullpath);

	static void jsonToFile(rapidjson::Document &jsonObj, std::string fullPath);

	/**
	 *	Converts rapidjson::Document object into a string
	 *	@param rapidjson::Document
	 *	@return std::string string for the given Document
	 */
	static std::string docToString(rapidjson::Document &jsonObj);

	

public:

	/**
     *	Saves the current tileMap in json-format into "tilemap.json"
     */
	static void saveMap();

    /**
     *	Loads tileMap data from file
     */
	static void loadMap(TileMapLayer *tileMap);

	/**
	 *	Writes a json-string into file on disk
	 *	@param json a string of json objects
	 *	@param fullPath use getPath() to get a writable path
	 */
	static bool tileMapSaveExists();

	static bool beeHiveSaveExists();

	static bool honeyExtractorSaveExists();

	static bool timesSaveExists();

	static bool moneySaveExists();

	/**
	 *	Saves all beeHives on the current tileMap into a json-array and writes them into "beehives.json"
	 */
	static void saveBeehives();

	/**
	 *	reads all beehives from "beehives.json" and returns them
	 */
	static void loadBeehives();

	/**
	 *	Saves all honeyExtractors on current tileMap into a json-array and writes them into "honeyextractors.json"
	 */
	static void saveHoneyExtractors();

	/**
	 *	reads all honeyExtractors from "honeyextractors.json" and returns them
	 */
    static void loadHoneyExtractors();

	/**
	 *	calls all other save methods for easier access
	 */
	static void saveEverything();

	/**
	 *	saves time to "times.json"
	 */
	static void saveTime();

	/**
	 *	saves money to "money.json"
	 */
	static void saveMoney();

	/**
	 *	reads time from "times.json" and returns it
	 */
	static void loadTime();

	/**
	 *	reads money from "money.json" and returns it
	 */
	static void loadMoney();

	/**
	 *	if it exists, deletes "tilemap.json"
	 */
	static void deleteTileMapSave();

	/**
     *	if it exists, deletes "beehives.json"
     */
	static void deleteBeeHivesSave();

	/**
	 *	if it exists, deletes "honeyextractors.json"
	 */
	static void deleteHoneyExtractorsSave();

	/**
	 *	if it exists, deletes "times.json"
	 */
	static void deleteTimeSave();

	/**
	 *	if it exists, deletes "money.json"
	 */
	static void deleteMoneySave();

	/**
	 *	calls all other delete methods for easier access
	 */
	static void deleteEverything();
};

#endif //SAVELOAD_H