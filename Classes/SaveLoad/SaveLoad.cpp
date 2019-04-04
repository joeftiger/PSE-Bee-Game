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

SaveLoad::SaveLoad()
{
}

void SaveLoad::saveMap(TMXTiledMap* map)
{
	auto layer = map->getLayer("objects");

    rapidjson::Document d;
    rapidjson::StringBuffer s;
    Writer<rapidjson::StringBuffer> writer(s);
    writer.StartObject();
	writer.Key("yo");
	writer.String("asldmas");
	for (int i = 0; i < map->getMapSize().width - 1; i++) {
	    writer.Key("row");
	    writer.StartArray();
		for (int j = 0; j < map->getMapSize().height - 1; j++) {
            writer.Uint(layer->getTileGIDAt(Vec2(i,j)));
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
	cocos2d::log("%s %s","path",  path.c_str());
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
	
	std::ofstream ofs{ R"(C:/Users/Tobias/AppData/Local/PSE-Bee-Game/tilemap.json)" };
	if (!ofs.is_open()) {
		log("%s", "Couldn't open file");
	}
	OStreamWrapper osw(ofs);
	Writer<OStreamWrapper> out(osw);
	jsonObj.Accept(out);
}

/**
	Converts rapidjson::Document object into a string
*/
std::string SaveLoad::jsonToString(rapidjson::Document &jsonObj) {
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(buffer);
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
	Writer<StringBuffer> writer(buffer);
	d.Accept(writer);

	if (d.HasParseError()) {
		log("%u",d.GetParseError());
		return;
	}

	log("%s %s", "loaded", buffer.GetString());
	ifs.close();
}

bool SaveLoad::fileExists(std::string filename) {
	std::ifstream infile(filename);
	return infile.good();
}

void SaveLoad::saveBeehives(std::vector<BeeHive> BeeHives) {
	//different approach -> https://stackoverflow.com/questions/50728931/save-load-vector-of-object-using-rapidjson-c
	rapidjson::Document d;
	rapidjson::StringBuffer s;
	Writer<rapidjson::StringBuffer> writer(s);
	writer.StartObject();
	

	for (BeeHive b : BeeHives) {
		//TODO: add actual implementation for saving, add BeeHive.getPosition()
		
		writer.Key("Position");
		writer.StartArray();
		//writer.Int(b.getPosition().x)
		//writer.Int(b.getPosition().y)
		writer.EndArray();
		writer.Key("BeesAlive");
		writer.Int(b.beesAlive());
	}

	writer.EndObject();

	d.Parse(s.GetString());
	log("%s %s", "json1", s.GetString());
	jsonToFile(jsonToString(d), getPath("beehives.json"));
}

void SaveLoad::saveBeehive(std::vector<BeeHive> BeeHives) {
	rapidjson::Document doc;
	rapidjson::StringBuffer jsonBuffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
	doc.SetObject();
	rapidjson::Document subDoc(&doc.GetAllocator());

	for (BeeHive b : BeeHives) {
		b.toJSON(subDoc);
		doc.AddMember("BeeHive", subDoc, doc.GetAllocator());
	}

	doc.Accept(jsonWriter);
}

void SaveLoad::loadBeehives() {

}
