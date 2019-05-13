
#include "SaveLoad.h"
#include "Game/TileMapLayer.h"
#include "Game/Wallet.h"
#include "Game/Time.h"
#include "Game/BeeHive.h"
#include "Atlas/BeeHiveAtlas.h"
#include "Atlas/HoneyExtractorAtlas.h"
#include "Story/StoryScene.h"
#include "json/prettywriter.h"
#include "json/istreamwrapper.h"
#include "json/ostreamwrapper.h"
#include <iostream>
#include <fstream>
#include <json/stringbuffer.h>
#include <json/writer.h>

using namespace rapidjson;


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

	log("%s %s", "tileMapJson", s.GetString());
	d.Parse(s.GetString());

	jsonToFile(docToString(d), getPath("tilemap.json"));
}


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


void SaveLoad::jsonToFile(std::string json, std::string fullPath) {
	bool b = FileUtils::getInstance()->writeStringToFile(json, fullPath);
	if (b) {
		log("successfully wrote to file");
	}
}


std::string SaveLoad::docToString(rapidjson::Document &jsonObj) {
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(buffer);
	jsonObj.Accept(jsonWriter);
	return std::string(buffer.GetString());
}


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
	SaveLoad::saveMoney();
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


void SaveLoad::saveMoney() {
	rapidjson::Document doc;
	rapidjson::StringBuffer buffer;
	rapidjson::Writer <rapidjson::StringBuffer> jsonWriter(buffer);
	doc.SetArray();
	Wallet::getInstance()->toJSON(doc);

	doc.Accept(jsonWriter);
	jsonToFile(docToString(doc), getPath("money.json"));
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

void SaveLoad::loadMoney() {
	std::ifstream ifs(getPath("money.json"));

	if (!ifs.is_open()) {
		log("Couldn't load money");
		return;
	}

	IStreamWrapper isw(ifs);
	rapidjson::Document doc;
	doc.ParseStream(isw);

	Wallet::getInstance()->fromJSON(doc);
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

bool SaveLoad::moneySaveExists() {
	return FileUtils::getInstance()->isFileExist(getPath("money.json"));
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

void SaveLoad::deleteMoneySave() {
	FileUtils::getInstance()->removeFile(getPath("money.json"));
    assert(!moneySaveExists());
}


void SaveLoad::deleteEverything() {
	BeeHiveAtlas::getInstance()->clear();
	HoneyExtractorAtlas::getInstance()->clear();
	Wallet::getInstance()->clear();
	deleteBeeHivesSave();
	deleteHoneyExtractorsSave();
	deleteTileMapSave();
	deleteTimeSave();
	deleteMoneySave();
}

void SaveLoad::saveStory() {
    rapidjson::Document doc;
    rapidjson::StringBuffer jsonBuffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
    doc.SetArray();
    assert(doc.IsArray());
    StoryScene::getInstance()->toJSON(doc);

    doc.Accept(jsonWriter);
    jsonToFile(docToString(doc), getPath("story.json"));
}

void SaveLoad::loadStory() {
    std::ifstream ifs(getPath("story.json"));

    if (!ifs.is_open()) {
        log("Couldn't load states");
        return;
    }

    IStreamWrapper isw(ifs);
    rapidjson::Document doc;
    doc.ParseStream(isw);

    StoryScene::getInstance()->fromJSON(doc);
}