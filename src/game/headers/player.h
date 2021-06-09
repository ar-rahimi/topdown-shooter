//
// Created by Ahmad Rahimi on 9/26/17.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include "moveableobject.h"
#include <bullet.h>
#include <inputmanager.h>
#include "helper.h"
#include "wall.h"
class Bullet;

class Player : public MoveableObject{
public:
    Player();
    Player(std::string objectName, float x, float y, int timeToUpdate);
    void draw();
    void update(float elapsedTime);
    void changeDirection(float toX, float toY);
    void movePlayerLeft(std::string doAction);
    void movePlayerRight(std::string doAction);
    void movePlayerBack(std::string doAction);
    void movePlayerForward(std::string doAction);
    void shootWeapon();
    void stopShooting();
    void reloadWeapon();
    void stopPlayer();
    void checkInput(InputManager input);

    virtual void animationDone(std::string currentAnimation);
    virtual void animationEnded();
    virtual void setupAnimation();

private:
    bool waitForPrevAnimation;
    void doReloadOrShoot(std::string doAction);
    std::map<int, Bullet> bullets;
};

#endif //PLAYER_H
