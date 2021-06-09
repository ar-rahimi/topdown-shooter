//
// Created by Ahmad Rahimi on 9/25/17.
//

#include <SDL.h>
#include "assetsmanager.h"
#include <SDL_image.h>
#include <iostream>

AssetsManager* AssetsManager::assetsManager;

AssetsManager::AssetsManager() {

}
AssetsManager::~AssetsManager(){

}
SDL_Surface* AssetsManager::loadImage(const std::string &filePath) {
    if (this->_spriteSheets.count(filePath) == 0) {
        this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
    }
    return this->_spriteSheets[filePath];
}

AssetsManager* AssetsManager::getManager() {
    if (!assetsManager){
        assetsManager = new AssetsManager;
    }
    return assetsManager;
}