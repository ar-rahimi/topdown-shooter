//
// Created by Ahmad Rahimi on 10/1/17.
//
#include "wall.h"

std::map<int,Wall> Wall::walls;

Wall::Wall(){

}
Wall::Wall(std::string objectName, float x, float y) :
x(x), y(y){
    sprite = SpriteObject(Helper::getCurrentWorkingDir() + "/content/sprites/structures/" + objectName + ".png", x,y, 0);
    this->h = (float)sprite.h;
    this->w = (float)sprite.w;
}

void Wall::Draw() {
    sprite.draw(this->x, this->y, 0);
}

float Wall::getXPos(){
    return this->x;
}

float Wall::getYPos() {
    return this->y;
}

float Wall::getWidth() {
    return (float)sprite.w;
}

float Wall::getHeight(){
    return (float)sprite.h;
}