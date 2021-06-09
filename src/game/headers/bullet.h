//
// Created by Ahmad Rahimi on 9/26/17.
//

#ifndef BULLET_H
#define BULLET_H
#include "helper.h"
#include "animatedobject.h"
#include <Box2D/Box2D.h>
#include "wall.h"

class Bullet : AnimatedObject {
public:
    Bullet();
    ~Bullet();
    Bullet(std::string objectName, float x, float y, int timeToUpdate, double angle);
    void draw();
    void update(float elapsedTime);
    virtual void animationDone(std::string currentAnimation);
    virtual void animationEnded();
    virtual void setupAnimation();
    bool destroy;
    void bounce();
protected:
    float _dx, _dy, _x, _y;
    double _dir;
    double _rad;
    double _corrected_angle;
};
#endif //BULLET_H
