//
// Created by Ahmad Rahimi on 9/25/17.
//

#include "spriteobject.h"

SpriteObject::SpriteObject() {}

SpriteObject::SpriteObject(const std::string &filePath, float posX, float posY, int partnumber) : _x(posX), _y(posY), _partnumber(partnumber) {
    this->_sprite = SDL_CreateTextureFromSurface(RenderManager::getRenderManager()->getRenderer(), AssetsManager::getManager()->loadImage(filePath));

    if (this->_sprite == NULL){
        printf(SDL_GetError());
    }
}

SpriteObject::~SpriteObject() {}

void SpriteObject::draw(float x, float y, double angle) {
//    try {
    SDL_QueryTexture(this->_sprite, NULL, NULL, &this->w, &this->h);
    SDL_Rect destinationRectangle = {int(x), int(y), this->w, this->h};
    RenderManager::getRenderManager()->blitSurface(this->_sprite, NULL, &destinationRectangle, angle);
//    }catch (int e){
//        std::cout << "An exception occurred. Exception Nr. " << e << '\n';
//    }
}

void SpriteObject::update() {

}