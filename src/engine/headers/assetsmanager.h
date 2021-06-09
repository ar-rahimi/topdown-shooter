//
// Created by Ahmad Rahimi on 9/25/17.
//

#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <map>
#include <string>
#include <SDL.h>

class AssetsManager {
public:
    AssetsManager();
    ~AssetsManager();

    SDL_Surface* loadImage(const std::string &filePath);
    static AssetsManager* getManager();


private:
    std::map<std::string, SDL_Surface*> _spriteSheets;
    static AssetsManager *assetsManager;

};
#endif //ASSETSMANAGER_H
