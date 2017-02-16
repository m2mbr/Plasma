#ifndef __AIRCRAFT_H__
#define __AIRCRAFT_H__

#include "cocos2d.h"
#include "Aircraft.h"
#include "SimpleAudioEngine.h"
#include "Enums.h"
#include <vector>

class Arm;
class Meteor;
class PadControl;
class Aircraft : public cocos2d::Sprite
{
public:
    Aircraft();
    static Aircraft* create();
    void makeMove();
    void shotLaser();
    void addLaser(Arm* laser);
    void removeLaser(Arm* laser);
    void addPad(PadControl* padControl);
    bool findLaser(Arm* laser);
    void makeRotation(char side);
    float getAngle();
    CocosDenshion::SimpleAudioEngine* audio;
    Meteor* shotCollision(std::vector<Meteor*> meteors);
    cocos2d::Rect getBox();
    cocos2d::Size visibleSize;
private:
    std::vector<cocos2d::EventKeyboard::KeyCode> keys;
    std::vector<Arm*> lasers;
    Aircraft* pSprite;
    PadControl* padControl;
    virtual void update(float delta) override;
    void addPhysics();
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void initOptions();
    void addEvents();
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode KeyCode);
    void onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event);
};
#endif // __AIRCRAFT_H__
