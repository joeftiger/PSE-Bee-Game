//
// Created by julius on 31.03.19.
//

#ifndef PSE_BEE_GAME_RESTORABLE_H
#define PSE_BEE_GAME_RESTORABLE_H


#include "json/rapidjson.h"
#include "json/document.h"

class Restorable {
public:
    /**
     * Each implementing subclass must add its restorable information as members to the specified document.
     *
     * @param doc the document to store the important information
     */
    virtual void toJSON(rapidjson::Document &doc) = 0;

    /**
     * Each implementing subclass must read its restorable information from the specified document.
     * @param doc the document to read the important information
     */
    virtual void fromJSON(rapidjson::Document &doc) = 0;
};

#endif //PSE_BEE_GAME_RESTORABLE_H
