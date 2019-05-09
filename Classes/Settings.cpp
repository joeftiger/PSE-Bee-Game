
#include <cocos/base/CCConsole.h>
#include "Settings.h"

Settings::Settings() {
	cocos2d::log("Settings:\tCreating instance");
	set(SettingName::HD_Textures, true);
	set(SettingName::Tutorial, true);
}

std::string Settings::get(Settings::SettingName setting) {
	return _settings.at(setting);
}

bool Settings::getAsBool(Settings::SettingName setting) {
	return _settings.at(setting) == "1";
}

int Settings::getAsInt(Settings::SettingName setting) {
	return std::atoi(_settings.at(setting).c_str());
}

void Settings::set(Settings::SettingName setting, const std::string &value) {
	cocos2d::log("Setting %d to %s", setting, value);
	_settings[setting] = value;
}

void Settings::set(Settings::SettingName setting, bool value) {
	cocos2d::log("Setting %d to %i", setting, value);
	_settings[setting] = value ? "1" : "";
}

void Settings::set(Settings::SettingName setting, int value) {
	cocos2d::log("Setting %d to %i", setting, value);
	_settings[setting] = std::to_string(value);
}
