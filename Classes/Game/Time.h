#ifndef TIME_H
#define TIME_H

#include "cocos2d.h"
#include "HeaderFiles/DEFINITIONS.h"
#include "HeaderFiles/Restorable.h"
#include "HeaderFiles/TimeStruct.h"
#include "json/rapidjson.h"
#include "HeaderFiles/Seasons.h"

using namespace cocos2d;

class Time: public Node, Restorable  {
private:
	static Time *_instance;

	Time() = default;

	Time(const Time &);

	~Time() = default;

	timeStruct times;

	std::string convertToMonth(int i);

	void time(float dt);

public:

	virtual bool init();

	static Time * createInstance();

	static Time * getInstance();

	bool invariant();

	int getMonth();

	void setStartingMonth();

	std::string getMonthAsString();

	Season getSeason();

	void toJSON(rapidjson::Document &doc);

	void fromJSON(rapidjson::Document &doc);

	CREATE_FUNC(Time);
};


#endif //TIME_H


