#include "Control.h"
USING_NS_CC;

Control::Control()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
}

Control* Control::create()
{
    Control* pSprite = new Control();
    auto pinfo = AutoPolygon::generatePolygon("res/Controls/flatLight49.png");
    if (pSprite->initWithPolygon(pinfo))
    {
        pSprite->addPhysics();
        pSprite->addEvents();
        pSprite->initOptions();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Control::addEvents()
{

    this->scheduleUpdate();
}

void Control::initOptions()
{
    this->setTag(Tags::control);
    this->getPhysicsBody()->setCategoryBitmask(0);
    this->getPhysicsBody()->setCollisionBitmask(0);
    this->getPhysicsBody()->setContactTestBitmask(true);
    this->setOpacity(150);
}

void Control::addPhysics()
{
    auto physicsBody = PhysicsBody::createCircle(this->getContentSize().width/2);
    physicsBody->setDynamic(false);
    this->addComponent(physicsBody);
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Control::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

Rect Control::getBox()
{
    return Director::getInstance()->getRunningScene()->getBoundingBox();
}

bool Control::onContactBegin(PhysicsContact& contact)
{
    return false;
}

float Control::getAngle()
{
    return fmod(this->getRotation(), 360);
}


Vec2 Control::getCenter()
{
    return Vec2(this->getParent()->getBoundingBox().size.width/2, this->getParent()->getBoundingBox().size.height/2);
}

float Control::getDistanceFromCenter(Vec2 pos)
{

    float dist = pos.distance(this->getCenter());
    return dist;
}
