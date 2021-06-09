//
// Created by Ahmad Rahimi on 10/1/17.
//

#ifndef WALL_H
#define WALL_H
#include <array>
#include "moveableobject.h"
#include <bullet.h>
#include <inputmanager.h>
#include "helper.h"
#include "spriteobject.h"

class Wall{
public:
    Wall();
    Wall(std::string objectName, float x, float y);
    void Draw();
    float getXPos();
    float getYPos();
    float getHeight();
    float getWidth();
    static std::map<int,Wall> walls;

private:
    SpriteObject sprite;
    float x;
    float y;
    float h;
    float w;
};

#endif //WALL_H
