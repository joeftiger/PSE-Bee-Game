//
// Created by Tobias on 27.04.2019.
//

#ifndef PROJ_ANDROID_INTERACTABLE_H
#define PROJ_ANDROID_INTERACTABLE_H

class Interactable {
private:


public:
    bool _interactable = true;

    virtual bool isInteractable() = 0;

    virtual void doTask() = 0;
};

#endif //PROJ_ANDROID_INTERACTABLE_H
