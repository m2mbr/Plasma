#include "Arm.h"
#include "Aircraft.h"

USING_NS_CC;

Arm::Arm()
{

}

Arm* Arm::create()
{
    Arm* pSprite = new Arm();
    if (pSprite->initWithFile("res/Lasers/laserRed01.png"))
    {
        // pSprite->physics();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}
void Arm::addEvents()
{

}

void Arm::update(float delta)
{

}

void Arm::physics()
{
    auto physicsBody = PhysicsBody::createBox(this->getContentSize(),
    PhysicsMaterial(1.0f, 0.0f, 0.0f)
    );
    physicsBody->setDynamic(true);
    this->addComponent(physicsBody);
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Arm::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

float Arm::getHeigth()
{
    return this->getBoundingBox().size.height;
}

void Arm::shotLaser()
{
    Vec2 location = aircraft->getPosition();
    float angle = aircraft->getAngle();
    float radius = CC_DEGREES_TO_RADIANS(angle);
    float r = aircraft->visibleSize.height * 1000;
    float dx = r * sin(radius);
    float dy = r * cos(radius);
    Vec2 destination = location + Vec2(dx, dy);
    float x = this->getContentSize().height * sin(radius);
    float y = this->getContentSize().height * cos(radius);
    this->setRotation(angle);
    location = location + Vec2(x,y);
    this->setPosition(location);
    aircraft->addLaser(this);
    aircraft->getParent()->addChild(this, -1);
    float distance = location.distance(destination);
    float time = distance/2000.0f;
    auto actionLaser = MoveTo::create(time, destination);
    this->runAction(actionLaser);
    this->aircraft->audio->playEffect("res/sfx_laser1.mp3");
}

void Arm::addToAircraft(Aircraft *aircraft)
{
    this->aircraft = aircraft;
}

void Arm::burstLaser()
{
    this->setTexture("res/Lasers/laserRed09.png");
}

bool Arm::onContactBegin(PhysicsContact& contact)
{
    return true;
}
