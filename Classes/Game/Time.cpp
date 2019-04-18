#include "Time.h"

Time *Time::_instance = nullptr;

bool Time::init() {
	if (!Node::init()) return false;

	this->schedule(schedule_selector(Time::time), UPDATE_TIME);

	return true;
}

/**
*	Creates a new Time-Instance
*	This is already called in GameScene, use getInstance() to get Time 
*/
Time *Time::createInstance() {
	
	_instance = Time::create();
	_instance->setName("time");
	return _instance;
}

Time *Time::getInstance() {
	return _instance;
}

void Time::time(float dt) {
	times.timePassed += dt;

	if (times.timePassed > 1) {
		times.timePassed = 0;
		times.seconds++;
	}

	if (times.seconds / 60 >= 1) {
		times.seconds = 0;
		times.months++;
	}

	if (times.months >= LENGTH_YEAR) {
		times.months = 0;
		times.years++;
	}
}

int Time::getMonth() {
	return times.months;
}

std::string Time::convertToMonth(int i)
{
	assert(i > 0 && i <= 12);

	switch (i) {
	case 1: return "Januar";
	case 2: return "Februar";
	case 3: return "März";
	case 4: return "April";
	case 5: return "Mai";
	case 6: return "Juni";
	case 7: return "July";
	case 8: return "August";
	case 9: return "September";
	case 10: return "Oktober";
	case 11: return "November";
	case 12: return "Dezember";
	default: return "not possible";
	}
}

void Time::toJSON(rapidjson::Document & doc) {
	rapidjson::Value obj(rapidjson::kObjectType);
	obj.AddMember("timePassed", times.timePassed, doc.GetAllocator());
	obj.AddMember("seconds", times.seconds, doc.GetAllocator());
	obj.AddMember("months", times.months, doc.GetAllocator());
	obj.AddMember("years", times.years, doc.GetAllocator());
	doc.PushBack(obj, doc.GetAllocator());
}

void Time::fromJSON(rapidjson::Document & doc) {
	assert(doc.IsArray());

	const rapidjson::Value &t = doc[0];

	assert(t["timePassed"].IsFloat());
	times.timePassed = t["timePassed"].GetFloat();

	assert(t["seconds"].IsInt());
	times.seconds = t["seconds"].GetInt();

	assert(t["months"].IsInt());
	times.months = t["months"].GetInt();

	assert(t["years"].IsInt());
	times.years = t["years"].GetInt();
}


