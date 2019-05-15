
#ifndef RESTORABLE_H
#define RESTORABLE_H


#include "json/rapidjson.h"
#include "json/document.h"

/**
 * Each implementing subclass must add and subtract its restorable information
 * as members to the specified document.
 */
class Restorable {
public:
	/**
	 * @param doc the document to store the important information
	 */
	virtual void toJSON(rapidjson::Document &doc) = 0;

	/**
	 * @param doc the document to read the important information
	 */
	virtual void fromJSON(rapidjson::Document &doc) = 0;
};

#endif //RESTORABLE_H
