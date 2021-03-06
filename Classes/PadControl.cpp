#include "PadControl.h"
#include "Aircraft.h"
#include "Control.h"

USING_NS_CC;

PadControl::PadControl()
{
    control = Control::create();
}

PadControl* PadControl::create()
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
    // listener1->onTouchesBegan = [&](const std::vector<Touch*>& touches, Event* event){
    //     auto bounds = event->getCurrentTarget()->getBoundingBox();
    //     for ( auto& touch : touches)
    //     {

    //     }
    // };

    listener1->onTouchesEnded = [&](const std::vector<Touch*>& touches, Event* event){
        for ( auto& touch : touches)
        {
            auto moveTo = MoveTo::create(0.4, getCenter());
            control->runAction(moveTo);
            distanceFromCenter = 0;
        }
    };

    listener1->onTouchesMoved = [&](const std::vector<Touch*>& touches, Event* event){
        for ( auto& touch : touches)
        {
            destTouch = control->getPosition() + touch->getDelta();
            distanceFromCenter = control->getDistanceFromCenter(destTouch);
            if (distanceFromCenter <= control->limit()){
                control->setPosition(destTouch);
                angleControl = control->getAngleControl(destTouch);
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

float PadControl::getAngleControl()
{
    return this->angleControl;
}

float PadControl::getDistanceFromCenter()
{
    return distanceFromCenter;
}