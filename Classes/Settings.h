//
// Created by julius on 04.05.19.
//

#ifndef PSE_BEE_GAME_SETTINGS_H
#define PSE_BEE_GAME_SETTINGS_H

#include <map>
#include <string>
#include "Observable.h"

class Settings : public Observable {
public:
	typedef enum {
		HD_Resolution
	} SettingName;

private:
	std::map<SettingName, std::string> _settings;

public:
	static Settings *getInstance() {
		static auto instance = new Settings;
		return instance;
	}

	/**
	 * Returns the raw string value of the setting
	 * @param name
	 * @return
	 */
	std::string get(const SettingName &name);

	bool getBool(const SettingName &name);
};


#endif //PSE_BEE_GAME_SETTINGS_H
