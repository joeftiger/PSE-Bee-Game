#ifndef TIME_H
#define TIME_H

#include "cocos2d.h"
#include "HeaderFiles/DEFINITIONS.h"
#include "HeaderFiles/Restorable.h"
#include "HeaderFiles/TimeStruct.h"
#include "json/rapidjson.h"

using namespace cocos2d;

class Time: public Node, Restorable  {
private:
	static Time *_instance;

	Time() = default;

	Time(const Time &);

	~Time() = default;

	timeStruct times;

public:

	virtual bool init();

	static Time * createInstance();

	static Time * getInstance();

	void time(float dt);

	int getMonth();

	std::string convertToMonth(int i);

	void toJSON(rapidjson::Document &doc);

	void fromJSON(rapidjson::Document &doc);

	CREATE_FUNC(Time);
};


#endif //TIME_H