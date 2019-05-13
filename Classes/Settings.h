
#ifndef PSE_BEE_GAME_SETTINGS_H
#define PSE_BEE_GAME_SETTINGS_H


#include <map>

/**
 * collection of settings and methods to interact with them for the game
 */
class Settings {
public:
	enum Option {
		HD_Textures = 0,
		Show_Tutorial = 1,
		Map_Scale = 2
	};

	float _mapScale;

private:
	std::map<Option, std::string> _settings;

	Settings();

public:
	static Settings *getInstance() {
		static auto instance = new Settings;
		return instance;
	}

	/**
	 * Returns the value for the given option.
	 * If no such value present, returns a <code>nullptr</code>
	 * @param option name of option
	 * @return raw value
	 */
	std::string get(Option option);

	/**
	 * Returns the bool value for the given option.
	 * If no such value present, returns a <code>false</code>
	 * @param option name of option
	 * @return bool value
	 */
	bool getAsBool(Option option);

	/**
	 * Returns the int value for the given option.
	 * If no such value present, returns a <code>0</code>
	 * @param option name of option
	 * @return int value
	 */
	int getAsInt(Option option);

	/**
	 * Returns the float value for the given option.
	 * If no such value present, returns a <code>0</code>
	 * @param option name of option
	 * @return float value
	 */
	float getAsFloat(Option option);

	/**
	 * Sets the value for the given option.
	 * @param option name of option
	 * @param value raw value
	 */
	void set(Option option, const std::string &value);

	/**
	 * Sets the bool value for the given option.
	 * @param option name of option
	 * @param value bool value
	 */
	void set(Option option, bool value);

	/**
	 * Sets the int value for the given option.
	 * @param option name of option
	 * @param value int value
	 */
	void set(Option option, int value);

	/**
	 * Sets the float value for the given option.
	 * @param option name of option
	 * @param value float value
	 */
	void set(Option option, float value);
};


#endif //PSE_BEE_GAME_SETTINGS_H
