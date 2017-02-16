#include "PadControl.h"
#include "Aircraft.h"
#include "Control.h"

USING_NS_CC;

PadControl::PadControl()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    control = Control::create();
}

PadControl* PadControl::create(Aircraft* aircraft)
{
    PadControl* pSprite = new PadControl();
    auto pinfo = AutoPolygon::generatePolygon("res/Controls/flatLight05.png");
    if (pSprite->initWithPolygon(pinfo))
    {
        pSprite->addPhysics();
        pSprite->initOptions();
        pSprite->initControl(); 
        pSprite->addEvents();

        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void PadControl::addPhysics()
{
    auto physicsBody = PhysicsBody::createCircle(this->getContentSize().width/2);
    physicsBody->setDynamic(false);
    this->addComponent(physicsBody);
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(PadControl::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool PadControl::onContactBegin(PhysicsContact& contact)
{
    return false;
}

void PadControl::addEvents()
{
    auto listener1 = EventListenerTouchAllAtOnce::create();
    listener1->onTouchesBegan = [&](const std::vector<Touch*>& touches, Event* event){
        auto bounds = event->getCurrentTarget()->getBoundingBox();
        for ( auto& touch : touches)
        {

        }
    };

    // listener->onTouchEnded = [&](Touch* touch, Event* event){
    //     // auto target = static_cast<Sprite*>(event->getCurrentTarget());
    //     // float r = this->getContentSize().height/2;
    //     // control->setPosition(r, r);
    //     // _angle = 0.0f;
    // };

    listener1->onTouchesMoved = [&](const std::vector<Touch*>& touches, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        for ( auto& touch : touches)
        {
            Vec2 dest = control->getPosition() + touch->getDelta();
            if (control->getDistanceFromCenter(dest) <= 32.0f){
                control->setPosition(dest); 
            }
        }
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, control);
    this->scheduleUpdate();
}

void PadControl::update(float delta)
{

}

void PadControl::initOptions()
{
    this->getPhysicsBody()->setCategoryBitmask(10);
    this->getPhysicsBody()->setCollisionBitmask(0);
    this->setPosition(
        Vec2(origin.x + this->getContentSize().width, origin.y + this->getContentSize().height)
    );
    this->setOpacity(150);
}

Rect PadControl::getBox()
{
    return Director::getInstance()->getRunningScene()->getBoundingBox();
}

void PadControl::initControl()
{
    size = this->getContentSize();
    control->setPosition(
        Vec2(size.width/2, size.height/2)
    );
    this->addChild(control);
}

Vec2 PadControl::getCenter()
{
    return Vec2(this->getBoundingBox().size.width/2, this->getBoundingBox().size.height/2);
}

float PadControl::getAngle(cocos2d::Vec2 pos)
{
    return fmod(this->getRotation(), 360);
}

float PadControl::getAngleControl()
{
    return _angle;
}
