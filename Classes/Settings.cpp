
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
	_settings[setting] = value;
}

void Settings::set(Settings::SettingName setting, bool value) {
	auto val = value ? "1" : "0";
	_settings[setting] = val;
}

void Settings::set(Settings::SettingName setting, int value) {
	_settings[setting] = std::to_string(value);
}

void Settings::setMapScale(float scale) {
    _mapScale = scale;
}

float Settings::getMapScale() {
    return _mapScale;
}