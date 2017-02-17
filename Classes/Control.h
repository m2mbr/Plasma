#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "cocos2d.h"
#include "Enums.h"

class Control : public cocos2d::Sprite
{
public:
    Control();
    static Control* create();
    cocos2d::Rect getBox();
    cocos2d::Vec2 getCenter();
    float getAngleControl(cocos2d::Vec2 pos);
    void setAngleControl(float angle);
    float getDistanceFromCenter(cocos2d::Vec2 pos);
    float limit();
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
