//
// Created by Ahmad Rahimi on 9/26/17.
//
#include "bullet.h"

namespace bullet_constants {
    const float BULLET_SPEED = 0.8f;
}

Bullet::Bullet() {}

Bullet::Bullet(std::string objectName, float x, float y, int timeToUpdate, double _dir) : AnimatedObject(objectName, x ,y, timeToUpdate) {
    this->setupAnimation();
    this->playAnimation("bullet_type_1");
    this->_corrected_angle = Helper::correctTheAngle(_dir);
    this->_dir = _dir;
    this->_x = x;
    this->_y = y;
    this->destroy = false;
}
Bullet::~Bullet() {

}

void Bullet::setupAnimation() {
    this->addAnimation( 0, "bullet_type_1");
}

void Bullet::draw() {
//    try {
//        if (this->_sprite._sprite != NULL) {
    AnimatedObject::drawsprite(this->_x, this->_y, this->_dir);
//        }
//    }catch (int e){
//        std::cout << "An exception occurred. Exception Nr. " << e << '\n';
//    }

}

void Bullet::bounce(){
    this->_dir = Helper::getNewDirection(this->_dir);
    this->_corrected_angle = Helper::correctTheAngle(this->_dir);
}

void Bullet::update(float elapsedTime) {
    for(auto &ent1 : Wall::walls) {
        if(this->_y > ent1.second.getYPos() && this->_x > ent1.second.getXPos() &&
           this->_y < (ent1.second.getYPos() + ent1.second.getHeight()) && this->_x < ent1.second.getXPos() + ent1.second.getWidth()){
            this->bounce();
            break;
        }
    }
    double correctedAngleRadians = Helper::degreesToRadians(this->_corrected_angle);
    this->_dx = bullet_constants::BULLET_SPEED * sin(correctedAngleRadians);
    this->_dy = bullet_constants::BULLET_SPEED * -cos(correctedAngleRadians);
    //movement times elapsedtime so we fill slower/faster framerate gaps
    this->_x += this->_dx * elapsedTime;
    this->_y += this->_dy * elapsedTime;

    AnimatedObject::update(elapsedTime);
}

void Bullet::animationDone(std::string currentAnimation) {

}


void Bullet::animationEnded() {

}