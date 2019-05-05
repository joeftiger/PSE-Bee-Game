//
// Created by julius on 05.05.19.
//

#include <cocos/base/CCConsole.h>
#include "Settings.h"

Settings::Settings() {
	cocos2d::log("Settings:\tCreating instance");
	set(SettingName::HD_Textures, true);
}

std::string Settings::get(Settings::SettingName setting) {
	return _settings.at(setting);
}

bool Settings::getAsBool(Settings::SettingName setting) {
	try {
		return _settings.at(setting) == "1";
	} catch (const std::out_of_range &e) {
		return false;
	}
}

void Settings::set(Settings::SettingName setting, const std::string &value) {
	_settings[setting] = value;
}

void Settings::set(Settings::SettingName setting, bool value) {
	_settings[setting] = value ? _true : _false;
}
