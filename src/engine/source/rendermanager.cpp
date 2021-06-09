//
// Created by Ahmad Rahimi on 9/25/17.
//

#include "rendermanager.h"


RenderManager* RenderManager::renderManager;

RenderManager::RenderManager() {
    SDL_CreateWindowAndRenderer(1500,960,0, &this->_window, &this->_renderer);
    SDL_SetWindowTitle(this->_window, "Shooter");
    SDL_Surface* surface = SDL_GetWindowSurface(this->_window);
    b2Vec2 gravity(0,-9.8);

    float32 timeStep = 1/20.0;      //the length of time passed to simulate (seconds)
    int32 velocityIterations = 8;   //how strongly to correct velocity
    int32 positionIterations = 3;   //how strongly to correct position

    world = new b2World(gravity);
    ContactListener *_contactListener;
    _contactListener = new ContactListener();
    world->SetContactListener(_contactListener);

    world->Step( timeStep, velocityIterations, positionIterations);

    world->SetAllowSleeping(false);
}

RenderManager::~RenderManager(){
    SDL_DestroyWindow(this->_window);
}

SDL_Surface* RenderManager::loadImage(const std::string &filePath) {
    if (this->_spriteSheets.count(filePath) == 0) {
        this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
    }
    return this->_spriteSheets[filePath];
}

void RenderManager::blitSurface(SDL_Texture *texture, SDL_Rect *sourceRectangle, SDL_Rect *destinationRectangle, double angle) {
    int resp = SDL_RenderCopyEx(this->_renderer, texture, sourceRectangle, destinationRectangle, angle, NULL, SDL_FLIP_HORIZONTAL);
//    std::cout << resp << std::endl;
    if (resp != 0) {
        std::cout << SDL_GetError() << std::endl;
    }

////    _rendercount += 1;
//    std::cout << std::to_string(_rendercount) << std::endl;
}

RenderManager* RenderManager::getRenderManager() {
    if(!renderManager){
        renderManager = new RenderManager;
    }
    return renderManager;
}

void RenderManager::flip(){
    SDL_RenderPresent(this->_renderer);
}

void RenderManager::clear() {
    SDL_RenderClear(this->_renderer);
}

SDL_Renderer* RenderManager::getRenderer() const {
    return this->_renderer;
}