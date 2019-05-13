
#include <cocos/base/CCConsole.h>
#include <HeaderFiles/DEFINITIONS.h>
#include "Settings.h"

Settings::Settings() {
	cocos2d::log("Settings:\tCreating instance");
	set(Option::HD_Textures, true);
	set(Option::Show_Tutorial, true);
	set(Option::Map_Scale, MAP_SCALE_HD);
}

std::string Settings::get(Settings::Option option) {
	return _settings.at(option);
}

bool Settings::getAsBool(Settings::Option option) {
	return get(option) == "1";
}

int Settings::getAsInt(Settings::Option option) {
	return std::atoi(get(option).c_str());
}

float Settings::getAsFloat(Settings::Option option) {
	return static_cast<float>(std::atof(get(option).c_str()));
}

void Settings::set(Settings::Option option, const std::string &value) {
	_settings[option] = value;
}

void Settings::set(Settings::Option option, bool value) {
	std::string val = value ? "1" : "";
	set(option, val);
}

void Settings::set(Settings::Option option, int value) {
	set(option, std::to_string(value));
}

void Settings::set(Settings::Option option, float value) {
	set(option, std::to_string(value));
}
