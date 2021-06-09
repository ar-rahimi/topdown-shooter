//
// Created by Ahmad Rahimi on 9/5/17.
//
#include <iostream>
#include <SDL.h>
#include <thread>
#include "game.h"

namespace {
    const int FPS = 50;
    const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    this->gameLoop();
}

Game::~Game() {

}

void Game::gameLoop() {
    RenderManager::getRenderManager();
    InputManager input;
    SDL_Event event;
    this->_player = Player("player", 300,300, 35);
    this->wall = Wall("wall", 250,200);
    int LAST_UPDATE_TIME = SDL_GetTicks();
    Wall::walls = {{0,this->wall}};
    for(int i = 1; i < 20; i++){
        int x = std::rand() % 1500;
        int y = std::rand() % 960;
        std::cout << x << std::endl;
        Wall::walls[i] = Wall("wall", x, y);
    }

    while (true) {
        input.beginNewFrame();

        if (SDL_PollEvent(&event)){
            if (event.type == SDL_KEYDOWN) {
                if(event.key.repeat == 0) {
                    input.keyDownEvent(event);
                }
            }else if (event.type == SDL_KEYUP){
                input.keyUpEvent(event);
            }

            if(event.type == SDL_MOUSEBUTTONDOWN){
                if(event.key.repeat == 0) {
                    input.mouseDownEvent(event);
                }
            }else if(event.type == SDL_MOUSEBUTTONUP){
                input.mouseUpEvent(event);
            }else if(event.type == SDL_MOUSEMOTION){
                input.mouseMovedEvent(event);
                this->_player.changeDirection(event.motion.x, event.motion.y);
            }

            if (event.type == SDL_QUIT){
                return;
            }
        }
        this->_player.checkInput(input);

        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
        this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME_MS;
        this->draw();
    }
}

void Game::draw() {
//    graphics.clear();
//    this->_player.draw(graphics);
////    this->_player_s.draw(graphics,300,300);
//    graphics.flip();
    RenderManager::getRenderManager()->clear();
    this->_player.draw();
    for(auto &it : Wall::walls){
        it.second.Draw();
    }
    RenderManager::getRenderManager()->flip();
}

void Game::update(float elapsedtime){
    _player.update(elapsedtime);
}