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

using namespace rapidjson;

SaveLoad::SaveLoad() {
}

void SaveLoad::saveMap(TMXTiledMap *map) {
	auto layer = map->getLayer("objects");

	rapidjson::Document d;
	rapidjson::StringBuffer s;
	Writer <rapidjson::StringBuffer> writer(s);
	writer.StartObject();
	writer.Key("yo");
	writer.String("asldmas");
	for (int i = 0; i < map->getMapSize().width - 1; i++) {
		writer.Key("row");
		writer.StartArray();
		for (int j = 0; j < map->getMapSize().height - 1; j++) {
			writer.Uint(layer->getTileGIDAt(Vec2(i, j)));
		}
		writer.EndArray();
	}

	//TODO: save honey, money, beehives to json

	writer.EndObject();
	log("%s %s", "json1", s.GetString());
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
void SaveLoad::loadMap() {
	std::string path = getPath("tilemap.json");
	std::ifstream ifs(path);

	if (!ifs.is_open()) {
		log("%s", "Couldn't load map");
		return;
	}

	IStreamWrapper isw(ifs);
	rapidjson::Document d;
	d.ParseStream(isw);

	StringBuffer buffer;
	Writer <StringBuffer> writer(buffer);
	d.Accept(writer);

	if (d.HasParseError()) {
		log("%u", d.GetParseError());
		return;
	}

	log("%s %s", "loaded", buffer.GetString());
	ifs.close();
}

bool SaveLoad::fileExists(std::string filename) {
	std::ifstream infile(filename);
	return infile.good();
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

	//StringBuffer buffer;
	//Writer<StringBuffer> writer(buffer);
	//doc.Accept(writer);
	//log("%s %s", "loaded", buffer.GetString());

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
		//TODO: Add new beehives to list
	}
}
