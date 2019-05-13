
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

	rapidjson::Document d;
	tileMapLayer->toJSON(d);
	
	jsonToFile(docToString(d), getPath("tilemap.json"));
}


std::string SaveLoad::getPath(std::string fileName) {
	auto fs = FileUtils::getInstance();
	std::string path = fs->getWritablePath();
	if (!fs->isDirectoryExist(path + "saves/")) {
		fs->createDirectory(path + "saves/");
	}
	path = path + "saves/" + fileName;
	//cocos2d::log("%s %s", "writable path", path.c_str());
	return path;
}


void SaveLoad::jsonToFile(std::string json, std::string fullPath) {
	if (FileUtils::getInstance()->writeStringToFile(json, fullPath)) {
		log("Writing to %s successful", fullPath.c_str());
	}
}


std::string SaveLoad::docToString(rapidjson::Document &jsonObj) {
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(buffer);
	jsonObj.Accept(jsonWriter);
	return std::string(buffer.GetString());
}

void SaveLoad::loadMap(TileMapLayer *tileMap) {
	std::string path = getPath("tilemap.json");
	std::ifstream ifs(path);

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
	}
	ifs.close();

	tileMap->fromJSON(d);

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
	SaveLoad::saveStory();
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
	Time::getInstance()->clear();
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

bool SaveLoad::storySaveExists() {
	return FileUtils::getInstance()->isFileExist(getPath("story.json"));
}