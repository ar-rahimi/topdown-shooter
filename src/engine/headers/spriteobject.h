//
// Created by Ahmad Rahimi on 9/25/17.
//

#ifndef SPRITEOBJECT_H
#define SPRITEOBJECT_H

#include <string>
#include <SDL.h>
#include "rendermanager.h"
#include "assetsmanager.h"
class Graphics;

class SpriteObject{
public:
    SpriteObject();
    SpriteObject(const std::string &filePath, float posX, float posY, int partnumber);
    virtual ~SpriteObject();
    virtual void update();
    void draw(float x, float y, double angle);
    SDL_Texture* _sprite;
    int _partnumber;
    int w,h;
private:;
    float _x, _y;
};

#endif //SPRITEOBJECT_H
