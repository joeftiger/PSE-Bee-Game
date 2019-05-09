
#ifndef PSE_BEE_GAME_SETTINGS_H
#define PSE_BEE_GAME_SETTINGS_H


#include <map>

/**
 * collection of settings and methods to interact with them for the game
 */
class Settings {
public:
	enum SettingName {
		HD_Textures,
		Tutorial
	};

private:
	std::map<SettingName, std::string> _settings;

	std::string _true = "1";
	std::string _false = "0";

	Settings();

public:
	static Settings *getInstance() {
		static auto instance = new Settings;
		return instance;
	}

	/**
	 * Returns the value for the given setting.
	 * If no such value present, returns a <code>nullptr</code>
	 * @param setting name of setting
	 * @return raw value
	 */
	std::string get(SettingName setting);

	/**
	 * Returns the value for the given setting as bool with the restriction that only
	 * <code>setting == "1"</code> returns <code>true</code>
	 * @param setting name of setting
	 * @return bool value
	 */
	bool getAsBool(SettingName setting);

	/**
	 * Sets the value for the given setting.
	 * @param setting name of setting
	 * @param value raw value
	 */
	void set(SettingName setting, const std::string &value);

	/**
	 * Sets the bool value for the given setting.
	 * @param setting name of setting
	 * @param value bool value
	 */
	void set(SettingName setting, bool value);
};


#endif //PSE_BEE_GAME_SETTINGS_H
