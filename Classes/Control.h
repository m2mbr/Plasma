#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "cocos2d.h"
#include "Enums.h"

class Control : public cocos2d::Sprite
{
public:
    Control();
    static Control* create();
    float getAngle(cocos2d::Vec2 pos);
    cocos2d::Rect getBox();
    cocos2d::Vec2 getCenter();
    float getDistanceFromCenter(cocos2d::Vec2 pos);
    cocos2d::Size visibleSize;
private:
    Control* pSprite;
    cocos2d::Vec2 origin;
    void initOptions();
    void addEvents();
    void addPhysics();
    bool onContactBegin(cocos2d::PhysicsContact& contact);
};
#endif // __CONTROL_H__
