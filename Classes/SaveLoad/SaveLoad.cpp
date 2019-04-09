#include <json/document.h>
#include <json/stringbuffer.h>
#include <json/writer.h>
#include <iostream>
#include <fstream>
#include "SaveLoad.h"
#include "json/rapidjson.h"
#include "json/istreamwrapper.h"
#include "json/ostreamwrapper.h"
#include "json/prettywriter.h"
#include "Game/GameScene.h"

using namespace rapidjson;

SaveLoad::SaveLoad() {
}

void SaveLoad::saveMap() {
	auto tileMapLayer = (TileMapLayer *)cocos2d::Director::getInstance()->getRunningScene()->getChildByName("TileMapLayer");
	auto layer = tileMapLayer->getLayer();

	rapidjson::Document d;
	rapidjson::StringBuffer s;
	Writer <rapidjson::StringBuffer> writer(s);
	writer.StartObject();
	for (int i = 0; i < layer->getLayerSize().width; i++) {
		writer.Key("row");
		writer.StartArray();
		for (int j = 0; j < layer->getLayerSize().height; j++) {
			writer.Uint(layer->getTileGIDAt(Vec2(i, j)));
		}
		writer.EndArray();
	}

	//TODO: save honey, money to json

	writer.EndObject();
	log("%s %s", "tileMapJson", s.GetString());
	d.Parse(s.GetString());

	jsonToFile(jsonToString(d), getPath("tilemap.json"));
}

/**
	Returns a writable path for the given filename
	@param fileName
*/
std::string SaveLoad::getPath(std::string fileName) {
	auto fs = FileUtils::getInstance();
	std::string path = fs->getWritablePath();
	if (!fs->isDirectoryExist(path + "saves/")) {
		fs->createDirectory(path + "saves/");
	}
	path = path + "saves/" + fileName;
	cocos2d::log("%s %s", "path", path.c_str());
	return path;
}

/**
	Writes a json-string into file on disk
	@param json
	@param fullPath
*/
void SaveLoad::jsonToFile(std::string json, std::string fullPath) {
	bool b = FileUtils::getInstance()->writeStringToFile(json, fullPath);
	if (b) {
		log("successfully wrote to file");
	}
}

/**
	Test-Method, currently unused
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
	Writer <OStreamWrapper> out(osw);
	jsonObj.Accept(out);
}

/**
	Converts rapidjson::Document object into a string
*/
std::string SaveLoad::jsonToString(rapidjson::Document &jsonObj) {
	rapidjson::StringBuffer buffer;
	rapidjson::Writer <rapidjson::StringBuffer> jsonWriter(buffer);
	jsonObj.Accept(jsonWriter);
	return std::string(buffer.GetString());
}


/**
	Loads data from disk
*/
std::vector<std::vector<int>> SaveLoad::loadMap() {
	std::string path = getPath("tilemap.json");
	std::ifstream ifs(path);

	std::vector<std::vector<int>> vec;
	std::vector<int> temp;

	if (!ifs.is_open()) {
		log("%s", "Couldn't load map");
		return vec;
	}

	IStreamWrapper isw(ifs);
	rapidjson::Document d;
	d.ParseStream(isw);

	StringBuffer buffer;
	Writer <StringBuffer> writer(buffer);
	d.Accept(writer);

	if (d.HasParseError()) {
		log("%u",d.GetParseError());
		return vec;
	}

	log("%s %s", "loaded", buffer.GetString());
	ifs.close();

	for (rapidjson::Value::ConstMemberIterator itr = d.MemberBegin(); itr != d.MemberEnd(); ++itr) {
		assert(itr->value.IsArray());
		for (auto& m : itr->value.GetArray()) {
			log("%i", m.GetInt());
			assert(m.IsInt());
			temp.push_back(m.GetInt());
		}
		vec.push_back(temp);
	}

	
	return vec;
}

bool SaveLoad::tileMapSaveExists() {
	return FileUtils::getInstance()->isFileExist(getPath("tilemap.json"));
}

bool SaveLoad::beeHiveSaveExists() {
	std::ifstream infile(getPath("beehives.json"));
	return infile.good();
}

void SaveLoad::deleteTileMapSave() {
	FileUtils::getInstance()->removeFile(getPath("tilemap.json"));
	assert(!tileMapSaveExists());
}

void SaveLoad::deleteBeeHivesSave() {
	FileUtils::getInstance()->removeFile(getPath("beehives.json"));
	assert(!beeHiveSaveExists());
}

void SaveLoad::saveBeehives(std::vector <BeeHive*> BeeHives) {

	rapidjson::Document doc;
	rapidjson::StringBuffer jsonBuffer;
	rapidjson::PrettyWriter <rapidjson::StringBuffer> jsonWriter(jsonBuffer);
	doc.SetArray();
	assert(doc.IsArray());
	for (auto b : BeeHives) {
		b->toJSON(doc);
	}
	doc.Accept(jsonWriter);
	jsonToFile(jsonToString(doc), getPath("beehives.json"));
}

void SaveLoad::loadBeehives() {
	std::ifstream ifs(getPath("beehives.json"));

	if (!ifs.is_open()) {
		log("Couldn't load beehives");
		return;
	}

	IStreamWrapper isw(ifs);
	rapidjson::Document doc;
	doc.ParseStream(isw);

	for (int i = 0; i < doc.Size(); i++) {
		rapidjson::Document subDoc;
		rapidjson::Value &data = doc[i];
		subDoc.SetObject();
		subDoc.AddMember("beeHive", data, subDoc.GetAllocator());

		StringBuffer buffer;
		Writer <StringBuffer> writer(buffer);
		subDoc.Accept(writer);
		log("BeeHive String %s", buffer.GetString());
		BeeHive b = BeeHive();
		b.fromJSON(subDoc);
	}
	//TODO: return all beeHives as vector?
}
