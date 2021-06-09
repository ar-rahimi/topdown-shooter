//
// Created by Ahmad Rahimi on 9/26/17.
//

#include "moveableobject.h"

MoveableObject::MoveableObject(){}

MoveableObject::MoveableObject(std::string objectName, float x, float y, int timeToUpdate) : AnimatedObject(objectName, x, y, timeToUpdate){
    this->setupAnimation();
    this->playAnimation("idle");
    this->playExtraAnimation("feet_idle");
    this->_x = x;
    this->_y = y;
    this->_dy = 0.0f;
    this->_dx = 0.0f;
//    this->myBodyDef->type = b2_dynamicBody;
//    myBodyDef->type = b2_dynamicBody;
//    myBodyDef->position.Set(x, y);
//    myBodyDef->angle = 0; //set the starting angle
}

void MoveableObject::animationDone(std::string currentAnimation) {

}

void MoveableObject::animationEnded() {
    waitForPrevAnimation = false;
    this->playAnimation("idle");
    this->playExtraAnimation("feet_idle");
}

void MoveableObject::setupAnimation() {
    this->addAnimation(19, "move");
    this->addAnimation(19, "idle");
    this->addAnimation(19, "shoot");
    this->addAnimation(19, "reload");
    this->addExtraAnimation(0, "feet_idle", 1);
    this->addExtraAnimation(19, "feet_strafe_left", 1);
    this->addExtraAnimation(19, "feet_strafe_right", 1);
    this->addExtraAnimation(19, "feet_walking", 1);
}

void MoveableObject::update(float elapsedTime) {
    //movement times elapsedtime so we fill slower/faster framerate gaps
    this->_x += this->_dx * elapsedTime;
    this->_y += this->_dy * elapsedTime;
    AnimatedObject::update(elapsedTime);
}

void MoveableObject::draw() {
    AnimatedObject::drawsprite(this->_x, this->_y, this->_dir);
}

void MoveableObject::changeDirection(float toX, float toY) {
    this->_rad = (atan2(this->_y - toY, this->_x - toX));
    this->_dir =  Helper::radiansToDegrees(_rad);
    this->myBodyDef->angle = this->_dir;
    if (this->_dir > 90){
        this->_corrected_angle = _dir - 90;
    }else if(this->_dir <= 90) {
        this->_corrected_angle = _dir + 270;
    }
}

void MoveableObject::AddToWorld(b2World* world){
    this->dynamicBody = world->CreateBody(this->myBodyDef);
}