//
// Created by Ahmad Rahimi on 9/25/17.
//

#include "animatedobject.h"
#include "helper.h"
#include <iostream>
AnimatedObject::AnimatedObject() {}

AnimatedObject::AnimatedObject(const std::string &objectName,
                               float posX, float posY, float timeToUpdate) :
        _frameIndex(0),
        _timeToUpdate(timeToUpdate),
        _visible(true),
        _currentAnimationLoop(true),
        _currentAnimation(""),
        _objectName(objectName){

}

void AnimatedObject::addAnimation(int maxFrames, std::string name) {
    std::map<int, SpriteObject> frames;
    for (int i = 0; i <= maxFrames; i++){
        frames[i] = SpriteObject(Helper::getCurrentWorkingDir() + "/content/sprites/" + _objectName + "/" + name + "/_" + std::to_string(i) + ".png", 200,200, 0);
    }
    this->_animations[name] = frames;
}

void AnimatedObject::addExtraAnimation(int maxFrames, std::string name, int partnumber) {
    std::map<int, SpriteObject> frames;
    for (int i = 0; i <= maxFrames; i++){
        frames[i] = SpriteObject(Helper::getCurrentWorkingDir() + "/content/sprites/" + _objectName + "/" + name + "/_" + std::to_string(i) + ".png", 200,200, partnumber);
    }
    this->_extraAnimations[name] = frames;
}

void AnimatedObject::resetAnimations() {
    this->_animations.clear();
}


void AnimatedObject::playAnimation(std::string animation, bool loop) {
    this->_currentAnimationLoop = loop;
    if(this->_currentAnimation != animation){
        this->_currentAnimation = animation;
        this->_frameIndex = 0;
    }
}

void AnimatedObject::playExtraAnimation(std::string animation, bool loop) {
    if (this->_extraAnimationsPlaying.find(animation) == this->_extraAnimationsPlaying.end()){
        for (auto it = this->_extraAnimationsPlaying.cbegin(); it != this->_extraAnimationsPlaying.cend();)
        {
            if (this->_extraAnimations[it->first][0]._partnumber == this->_extraAnimations[animation][0]._partnumber)
            {
                this->_extraAnimationsPlaying.erase(it++);
            }
            else
            {
                ++it;
            }
        }
        this->_extraAnimationsPlaying[animation] = 0;
    }
}

void AnimatedObject::setVisisble(bool visible) {
    this->_visible = visible;
}

void AnimatedObject::stopAnimations() {
    this->_frameIndex = 0;
    this->animationEnded();
}

void AnimatedObject::update(float elapsedTime) {
    this->_timeElapsed += elapsedTime;
    if (this->_timeElapsed > this->_timeToUpdate){
        this->_timeElapsed -= this->_timeToUpdate;
        if (this->_frameIndex < this->_animations[_currentAnimation].size() - 1){
            this->_frameIndex++;
        }else{
            if (!this->_currentAnimationLoop){
                animationEnded();
            }
            this->_frameIndex = 0;
            this->animationDone(this->_currentAnimation);
        }
        for (auto const &ent1 : this->_extraAnimationsPlaying){
            if (ent1.second < this->_extraAnimations[ent1.first].size() -1) {
                this->_extraAnimationsPlaying[ent1.first]++;
            }else{
                this->_extraAnimationsPlaying[ent1.first] = 0;
            }
        }
    }
}

void AnimatedObject::drawsprite(float x, float y, double angle) {
    if(this->_visible) {
        for (auto const &ent1 : this->_extraAnimationsPlaying){
            SpriteObject _extraanimation = this->_extraAnimations[ent1.first][ent1.second];
            _extraanimation.draw(x, y, angle);
        }
        this->_sprite = this->_animations[_currentAnimation][this->_frameIndex];
        this->_sprite.draw(x, y, angle);
    }
}