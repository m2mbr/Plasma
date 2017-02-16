#ifndef __ARM_H__
#define __ARM_H__

#include "cocos2d.h"

class Aircraft;
class Arm : public cocos2d::Sprite
{
public:
    Arm();
    static Arm* create();
    virtual void update(float delta) override;
    float getHeigth();
    void addToAircraft(Aircraft *aircraft);
    void shotLaser();
    void burstLaser();
private:
    void addEvents();
    void physics();
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    Aircraft *aircraft;
};

#endif // __ARM_H__
