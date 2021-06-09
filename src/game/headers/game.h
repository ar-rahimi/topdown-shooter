//
// Created by Ahmad Rahimi on 9/5/17.
//

#ifndef GAME_H
#define GAME_H

#include "rendermanager.h"
#include "wall.h"
#include "player.h"

class RenderManager;

class Game {
public:
    Game();
    ~Game();
private:
    void gameLoop();
    void draw();
    void update(float elapsedTime);

    Player _player;
    Wall wall;



};

#endif //SHOOTER_GAME_H
