#ifndef __PADCONTROL_H__
#define __PADCONTROL_H__

#include <algorithm>
#include <vector>
#include "cocos2d.h"


class Control;
class PadControl : public cocos2d::Sprite
{
public:
    PadControl();
    static PadControl* create();
    virtual void update(float delta) override;
    float getAngleControl();
    cocos2d::Rect getBox();
    cocos2d::Vec2 getCenter();
    float getDistanceFromCenter();

private:
    cocos2d::Size visibleSize;
    PadControl* pSprite;
    Control* control;
    cocos2d::Vec2 origin;
    cocos2d::Size size;
    float angleControl;
    float distanceFromCenter;
    void initOptions();
    void initControl();
    void addEvents();
    void addPhysics();
    bool onContactBegin(cocos2d::PhysicsContact& contact);
};
#endif // __PADCONTROL_H__
