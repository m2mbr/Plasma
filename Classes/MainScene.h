#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Aircraft.h"
#include "Meteor.h"
#include "Controls.h"
#include "PadControl.h"
#include <vector>
#include <algorithm>


class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    void setPhysicsWorld(cocos2d::PhysicsWorld* world) {
        World = world;
        World->setGravity(cocos2d::Vect(0, 0));
    }
    virtual bool init();
    virtual void update(float delta) override;
    cocos2d::PhysicsWorld* World;
    CREATE_FUNC(MainScene);
    cocos2d::Size visibleSize;
private:
    cocos2d::Rect box;
    Aircraft* sprite;
    PadControl* pad;
    std::vector<Meteor*> meteors;
    Controls* controls;
    void launchMeteors(unsigned int num);
    void removeMeteor(Meteor* meteor);
    bool findMeteor(Meteor* meteor);
    void addMeteor(Meteor* meteor);

};
#endif // __MAIN_SCENE_H__
