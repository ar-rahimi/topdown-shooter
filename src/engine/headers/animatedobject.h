//
// Created by Ahmad Rahimi on 9/25/17.
//

#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H

#include <map>
#include "spriteobject.h"
#include "assetsmanager.h"
#include "rendermanager.h"

class AnimatedObject {
public:
    AnimatedObject();
    AnimatedObject(const std::string &objectName, float posX, float posY, float timeToUpdate);

    void playAnimation(std::string animation, bool loop = true);

    void playExtraAnimation(std::string animation, bool loop = true);

    void update(float elapsedTime);

    void drawsprite(float x, float y, double angle);

protected:
    double _timeToUpdate;
    bool _currentAnimationLoop;
    std::string _currentAnimation;
    std::string _objectName;
    SpriteObject _sprite;

    void addAnimation(int maxFrames, std::string name);
    void addExtraAnimation(int maxFrames, std::string name, int partnumber);

    void resetAnimations();

    void stopAnimations();

    void setVisisble(bool visible);


    // = 0, omdat deze functies alleen beschikbaar moeten zijn van klasses die inheriten van animatedsprite klasse
    virtual void animationDone(std::string currentAnimation) = 0;

    virtual void animationEnded() = 0;

    virtual void setupAnimation() = 0;
private:
    std::map<std::string, std::map<int, SpriteObject> > _animations;
    std::map<std::string, std::map<int, SpriteObject> > _extraAnimations;
    std::map<std::string, int > _extraAnimationsPlaying;

    int _frameIndex;
    double _timeElapsed;
    bool _visible;
};

#endif //ANIMATEDOBJECT_H
