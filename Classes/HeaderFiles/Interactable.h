
#ifndef PROJ_ANDROID_INTERACTABLE_H
#define PROJ_ANDROID_INTERACTABLE_H

/**
 * Any class that implements interactable, has to implement interactability with sprites
 */
class Interactable {
private:

	std::string sprite;

public:
    bool _interactable = true;

    virtual bool isInteractable() = 0;

    virtual void doTask() = 0;
	
	virtual std::string getSprite() = 0;
};

#endif //PROJ_ANDROID_INTERACTABLE_H
