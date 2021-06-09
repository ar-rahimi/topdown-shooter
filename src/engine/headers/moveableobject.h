//
// Created by Ahmad Rahimi on 9/26/17.
//

#ifndef MOVEABLEOBJECT_H
#define MOVEABLEOBJECT_H

#include <array>
#include "animatedobject.h"
#include "helper.h"
#include <Box2D/Box2D.h>

class MoveableObject : public AnimatedObject{
public:
    MoveableObject();
    MoveableObject(std::string objectName, float x, float y, int timeToUpdate);
    void draw();
    void update(float elapsedTime);
    void changeDirection(float toX, float toY);
    void AddToWorld(b2World* world);
    virtual void animationDone(std::string currentAnimation);
    virtual void animationEnded();
    virtual void setupAnimation();

    float _dx, _dy, _x, _y;
    double _dir;
    double _rad;
    double _corrected_angle;

    b2BodyDef* myBodyDef;
    b2Body* dynamicBody;


private:
    bool waitForPrevAnimation;
};

#endif //MOVEABLEOBJECT_H
