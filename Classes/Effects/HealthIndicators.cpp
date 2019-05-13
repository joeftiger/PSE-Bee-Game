
#include "HealthIndicators.h"
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

Node *HealthIndicators::createNode() {return HealthIndicators::create();}

bool HealthIndicators::init() {
    if (!Node::init()) {
        return false;
    }

    return true;
}