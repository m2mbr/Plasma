#ifndef __METEOR_H__
#define __METEOR_H__

#include <vector>
#include "cocos2d.h"


class Meteor : public cocos2d::Sprite
{
public:
    Meteor();
    static Meteor* create();
    // virtual void update(float delta) override;
    void toMove();
    float getHeigth();
    void setAnimed(bool value);
    bool getAnimed();
private:
    void makeRotation();
    void makePositions();
    void makeResMeteors();
    void addEvents();
    void initOptions();
    void addPhysics();
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    float xMax();
    float yMin();
    float xMin();
    float yMax();
    float xRand();
    float yRand();
    std::string selectResMeteors(void);
    cocos2d::Vec2 selectPosition(void);
    cocos2d::Vec2 right();
    cocos2d::Vec2 left();
    cocos2d::Vec2 up();
    cocos2d::Vec2 down();
    bool animed = false;
    cocos2d::Size visibleSize;
    std::vector<cocos2d::Vec2> positions;
    std::vector<std::string> resMeteors;
};
#endif // __METEOR_H__
