//
// Created by Ahmad Rahimi on 9/6/17.
//

#include "player.h"


namespace player_constants {
    const float WALK_SPEED = 0.2f;
    const float OTHER_SPEED = 0.15f;
    float WEAPON_READY = 0;
}

Player::Player(){}

Player::Player(std::string objectName, float x, float y, int timeToUpdate) : MoveableObject(objectName, x, y, timeToUpdate){
    this->setupAnimation();
    this->playAnimation("idle");
    this->playExtraAnimation("feet_idle");
}

void Player::animationDone(std::string currentAnimation) {

}

void Player::animationEnded() {
    waitForPrevAnimation = false;
    this->playAnimation("idle");
    this->playExtraAnimation("feet_idle");
}

void Player::setupAnimation() {
    this->addAnimation(19, "move");
    this->addAnimation(19, "idle");
    this->addAnimation(19, "shoot");
    this->addAnimation(19, "reload");
    this->addExtraAnimation(0, "feet_idle", 1);
    this->addExtraAnimation(19, "feet_strafe_left", 1);
    this->addExtraAnimation(19, "feet_strafe_right", 1);
    this->addExtraAnimation(19, "feet_walking", 1);
}

void Player::update(float elapsedTime) {
    //movement times elapsedtime so we fill slower/faster framerate gaps
    this->_x += this->_dx * elapsedTime;
    this->_y += this->_dy * elapsedTime;
    player_constants::WEAPON_READY -= 0.01 * elapsedTime;
    for(auto &ent1 : this->bullets) {
        if(!ent1.second.destroy) {
            ent1.second.update(elapsedTime);
        }else{
            ent1.second.bounce();
        }
    }
//    auto i = std::begin(this->bullets);
//
//    while (i != std::end(this->bullets)) {
//        // Do some stuff
//        try {
//            if (i->second.destroy)
//                this->bullets.erase(i);
//            else
//                i->second.update(elapsedTime);
//            ++i;
//        }
//        catch (const std::exception& e){
//            std::cout << e.what();
//        }
//    }
    MoveableObject::update(elapsedTime);
}

void Player::draw() {
    MoveableObject::drawsprite(this->_x, this->_y, this->_dir);
    for(auto &ent1 : this->bullets) {
        ent1.second.draw();
    }
}

void Player::changeDirection(float toX, float toY) {
    this->_rad = (atan2(this->_y - toY, this->_x - toX));
    this->_dir =  Helper::radiansToDegrees(_rad);
    if (this->_dir > 90){
        this->_corrected_angle = _dir - 90;
    }else if(this->_dir <= 90) {
        this->_corrected_angle = _dir + 270;
    }
}

void Player::movePlayerForward(std::string doAction) {
    double correctedAngleRadians = Helper::degreesToRadians(this->_corrected_angle);
    this->_dx = player_constants::WALK_SPEED * sin(correctedAngleRadians);
    this->_dy = player_constants::WALK_SPEED * -cos(correctedAngleRadians);
    if(!waitForPrevAnimation) {
        if(doAction == "reload" | doAction == "shoot") {
            doReloadOrShoot(doAction);
        }else {
            this->playAnimation(doAction);
        }
    }
    this->playExtraAnimation("feet_walking");
}

void Player::doReloadOrShoot(std::string doAction) {
    waitForPrevAnimation = true;
    this->playAnimation(doAction, false);
}

void Player::movePlayerBack(std::string doAction) {
    double correctedAngleRadians = Helper::degreesToRadians((180 + this->_corrected_angle));
    this->_dx = player_constants::OTHER_SPEED * sin(correctedAngleRadians);
    this->_dy = player_constants::OTHER_SPEED * -cos(correctedAngleRadians);
    if(!waitForPrevAnimation) {
        if(doAction == "reload" | doAction == "shoot") {
            doReloadOrShoot(doAction);
        }else {
            this->playAnimation(doAction);
        }
    };
    this->playExtraAnimation("feet_walking");
}

void Player::movePlayerLeft(std::string doAction) {
    double correctedAngleRadians = Helper::degreesToRadians((-90 + this->_corrected_angle));
    this->_dx = player_constants::OTHER_SPEED * sin(correctedAngleRadians);
    this->_dy = player_constants::OTHER_SPEED * -cos(correctedAngleRadians);
    if(!waitForPrevAnimation) {
        if(doAction == "reload" | doAction == "shoot") {
            doReloadOrShoot(doAction);
        }else {
            this->playAnimation(doAction);
        }
    }
    this->playExtraAnimation("feet_strafe_left");
}

void Player::movePlayerRight(std::string doAction) {
    double correctedAngleRadians = Helper::degreesToRadians((90 + this->_corrected_angle));
    this->_dx = player_constants::OTHER_SPEED * sin(correctedAngleRadians);
    this->_dy = player_constants::OTHER_SPEED * -cos(correctedAngleRadians);
    if(!waitForPrevAnimation) {
        if((doAction == "reload" || doAction == "shoot") && player_constants::WEAPON_READY <= 0 ) {
            doReloadOrShoot(doAction);
        }else {
            this->playAnimation("move");
        }
    }
    this->playExtraAnimation("feet_strafe_right");
}

void Player::shootWeapon() {
    if(player_constants::WEAPON_READY <= 0) {
        player_constants::WEAPON_READY = 1.0;
        this->playAnimation("shoot");
        double correctedrad = Helper::degreesToRadians(_corrected_angle);

        //formule is heel fragiel, moet even naar gekeken worden of het beter kan
        float tipx = (float) ((_x + 50) + -50 * cos(correctedrad) - -28 * sin(_rad));
        float tipy = (float) ((_y + 35) + -2 * sin(correctedrad) + 19 * cos(_rad));

//    float tipx = (float) ((_x+50) + -25 * cos(correctedrad) - -28 * sin(correctedrad));
//    float tipy = (float) ((_y+35) + -20 * sin(correctedrad) + 19 * cos(correctedrad));

        Bullet bullet = Bullet("player", tipx, tipy, 100, this->_dir);
        this->bullets[this->bullets.size()] = bullet;
    }
}

void Player::stopShooting() {
    this->stopAnimations();
}

void Player::reloadWeapon() {
    this->playAnimation("reload", false);
}

void Player::stopPlayer() {
    this->_dx = 0.0f;
    this->_dy = 0.0f;
    this->stopAnimations();
}

void Player::checkInput(InputManager input) {
    std::string bodymovement;
    //do body movement
    if (input.isKeyHeld(SDL_SCANCODE_S) | input.isKeyHeld(SDL_SCANCODE_W) | input.isKeyHeld(SDL_SCANCODE_A) | input.isKeyHeld(SDL_SCANCODE_D)){
        bodymovement = "move";
        if(input.wasKeyPressed(SDL_SCANCODE_R)) {
            bodymovement = "reload";
        }
        else if (input.isMouseButtonHeld(SDL_BUTTON_LEFT)){
            bodymovement = "shoot";
        }
    }

    if(input.isKeyHeld(SDL_SCANCODE_W)){
        movePlayerForward(bodymovement);
    }else if(input.isKeyHeld(SDL_SCANCODE_S)){
        movePlayerBack(bodymovement);
    }else if(input.isKeyHeld(SDL_SCANCODE_D)){
        movePlayerRight(bodymovement);
    }else if(input.isKeyHeld(SDL_SCANCODE_A)){
        movePlayerLeft(bodymovement);
    }else if(input.wasKeyPressed(SDL_SCANCODE_R)){
        reloadWeapon();
    }
    if(input.isMouseButtonHeld(SDL_BUTTON_LEFT)){
        shootWeapon();
    }

    if(input.wasKeyReleased(SDL_SCANCODE_W) || input.wasKeyReleased(SDL_SCANCODE_S) || input.wasKeyReleased(SDL_SCANCODE_A) || input.wasKeyReleased(SDL_SCANCODE_D)){
        stopPlayer();
    }
    else if(input.wasMouseButtonReleased(SDL_BUTTON_LEFT)){
        stopShooting();
    }
}