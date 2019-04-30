
#include "SaveLoad.h"


using namespace rapidjson;

/**
 *	Saves the current tileMap in json-format into "tilemap.json"
 */
void SaveLoad::saveMap() {
	auto tileMapLayer = (TileMapLayer *) cocos2d::Director::getInstance()->getRunningScene()->getChildByName(
			TILE_MAP_LAYER_NAME);
	auto layer = tileMapLayer->getLayer();

	rapidjson::Document d;
	rapidjson::StringBuffer s;
	Writer<rapidjson::StringBuffer> writer(s);
	writer.StartObject();

	for (int i = 0; i < layer->getLayerSize().width; i++) {
		std::string s = std::to_string(i);
		writer.Key(s.c_str());
		writer.StartArray();
		for (int j = 0; j < layer->getLayerSize().height; j++) {
			writer.Uint(layer->getTileGIDAt(Vec2(i, j)));
		}
		writer.EndArray();
	}
	writer.EndObject();
	//TODO: save honey, money to json

	log("%s %s", "tileMapJson", s.GetString());
	d.Parse(s.GetString());

	jsonToFile(docToString(d), getPath("tilemap.json"));
}

/**
 *	Returns a writable path for the given filename
 *	@param fileName
 */
std::string SaveLoad::getPath(std::string fileName) {
	auto fs = FileUtils::getInstance();
	std::string path = fs->getWritablePath();
	if (!fs->isDirectoryExist(path + "saves/")) {
		fs->createDirectory(path + "saves/");
	}
	path = path + "saves/" + fileName;
	cocos2d::log("%s %s", "writable path", path.c_str());
	return path;
}

/**
 *	Writes a json-string into file on disk
 *	@param json a string of json objects
 *	@param fullPath use getPath() to get a writable path
 */
void SaveLoad::jsonToFile(std::string json, std::string fullPath) {
	bool b = FileUtils::getInstance()->writeStringToFile(json, fullPath);
	if (b) {
		log("successfully wrote to file");
	}
}

/**
 *	Converts rapidjson::Document object into a string
 *	@param rapidjson::Document
 *	@return std::string string for the given Document
 */
std::string SaveLoad::docToString(rapidjson::Document &jsonObj) {
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(buffer);
	jsonObj.Accept(jsonWriter);
	return std::string(buffer.GetString());
}

/**
 *	Loads tileMap data from file
 */
std::vector<std::vector<int>> SaveLoad::loadMap() {
	std::string path = getPath("tilemap.json");
	std::ifstream ifs(path);

	std::vector<std::vector<int>> vec;

	if (!ifs.is_open()) {
		log("%s", "Couldn't load map");
		std::ofstream f(getPath("tilemap.json"));
		f.close();
		std::ifstream ifs(getPath("tilemap.json"));
	}

	IStreamWrapper isw(ifs);
	rapidjson::Document d;
	d.ParseStream(isw);

	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	d.Accept(writer);

	if (d.HasParseError()) {
		log("%u", d.GetParseError());
		return vec;
	}

	ifs.close();
	for (rapidjson::Value::ConstMemberIterator itr = d.MemberBegin(); itr != d.MemberEnd(); ++itr) {
		assert(itr->value.IsArray());
		std::vector<int> temp;
		for (auto &m : itr->value.GetArray()) {
			assert(m.IsInt());
			temp.push_back(m.GetInt());
		}
		vec.push_back(temp);
	}

	return vec;
}

/**
 *	Saves all beeHives on the current tileMap into a json-array and writes them into "beehives.json"
 */
void SaveLoad::saveBeehives() {
	rapidjson::Document doc;
	rapidjson::StringBuffer jsonBuffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
	doc.SetArray();
	assert(doc.IsArray());
	BeeHiveAtlas::getInstance()->toJSON(doc);

	doc.Accept(jsonWriter);
	jsonToFile(docToString(doc), getPath("beehives.json"));
}

/**
 *	reads all beehives from "beehives.json" and returns them
 */
void SaveLoad::loadBeehives() {
	std::ifstream ifs(getPath("beehives.json"));

	if (!ifs.is_open()) {
		log("Couldn't load beehives");
		return;
	}

	IStreamWrapper isw(ifs);
	rapidjson::Document doc;
	doc.ParseStream(isw);

	BeeHiveAtlas::getInstance()->fromJSON(doc);

}

/**
 *	Saves all honeyExtractors on current tileMap into a json-array and writes them into "honeyextractors.json"
 */
void SaveLoad::saveHoneyExtractors() {
	rapidjson::Document doc;
	rapidjson::StringBuffer jsonBuffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
	doc.SetArray();
	assert(doc.IsArray());
	HoneyExtractorAtlas::getInstance()->toJSON(doc);

	doc.Accept(jsonWriter);
	jsonToFile(docToString(doc), getPath("honeyextractors.json"));
}

/**
 *	reads all honeyExtractors from "honeyextractors.json" and returns them
 */
void SaveLoad::loadHoneyExtractors() {
	std::ifstream ifs(getPath("honeyextractors.json"));

	if (!ifs.is_open()) {
		log("Couldn't load honeyextractors");
		return;
	}

	IStreamWrapper isw(ifs);
	rapidjson::Document doc;
	doc.ParseStream(isw);

	HoneyExtractorAtlas::getInstance()->fromJSON(doc);

}

void SaveLoad::saveEverything() {
	SaveLoad::saveBeehives();
	SaveLoad::saveHoneyExtractors();
	SaveLoad::saveMap();
	SaveLoad::saveTime();
}

void SaveLoad::saveTime() {
	rapidjson::Document doc;
	rapidjson::StringBuffer buffer;
	rapidjson::Writer <rapidjson::StringBuffer> jsonWriter(buffer);
	doc.SetArray();
	Time::getInstance()->toJSON(doc);

	doc.Accept(jsonWriter);
	jsonToFile(docToString(doc), getPath("times.json"));
}

void SaveLoad::loadTime() {
	std::ifstream ifs(getPath("times.json"));

	if (!ifs.is_open()) {
		log("Couldn't load times");
		return;
	}

	IStreamWrapper isw(ifs);
	rapidjson::Document doc;
	doc.ParseStream(isw);

	Time::getInstance()->fromJSON(doc);
}

/**
 *	Test-Method, currently unused
 */
void SaveLoad::jsonToFile(rapidjson::Document &jsonObj, std::string fullPath) {
	//	std::ofstream outputFile;
	//
	//	outputFile.open(fullPath);
	//	if (outputFile.is_open()) {
	//		std::string json = jsonToString(jsonObj);
	//		outputFile << json;
	//	}
	//	outputFile.close();

	std::ofstream ofs{R"(C:/Users/Tobias/AppData/Local/PSE-Bee-Game/tilemap.json)"};
	if (!ofs.is_open()) {
		log("%s", "Couldn't open file");
	}
	OStreamWrapper osw(ofs);
	Writer<OStreamWrapper> out(osw);
	jsonObj.Accept(out);
}

bool SaveLoad::tileMapSaveExists() {
	return FileUtils::getInstance()->isFileExist(getPath("tilemap.json"));
}

bool SaveLoad::beeHiveSaveExists() {
	return FileUtils::getInstance()->isFileExist(getPath("beehives.json"));
}

bool SaveLoad::honeyExtractorSaveExists() {
	return FileUtils::getInstance()->isFileExist(getPath("honeyextractors.json"));
}

bool SaveLoad::timesSaveExists() {
	return FileUtils::getInstance()->isFileExist(getPath("times.json"));
}

void SaveLoad::deleteTileMapSave() {
	FileUtils::getInstance()->removeFile(getPath("tilemap.json"));
	assert(!tileMapSaveExists());
}

void SaveLoad::deleteBeeHivesSave() {
	FileUtils::getInstance()->removeFile(getPath("beehives.json"));
	assert(!beeHiveSaveExists());
}

void SaveLoad::deleteHoneyExtractorsSave() {
	FileUtils::getInstance()->removeFile(getPath("honeyextractors.json"));
	assert(!honeyExtractorSaveExists());
}

void SaveLoad::deleteTimeSave() {
	FileUtils::getInstance()->removeFile(getPath("times.json"));
    assert(!timesSaveExists());
}

//  call all separate delete methods
void SaveLoad::deleteEverything() {
	BeeHiveAtlas::getInstance()->clear();
	HoneyExtractorAtlas::getInstance()->clear();
	deleteBeeHivesSave();
	deleteHoneyExtractorsSave();
	deleteTileMapSave();
	deleteTimeSave();
}