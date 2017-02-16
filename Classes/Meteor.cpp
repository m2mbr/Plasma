#include <algorithm>
#include "Meteor.h"
#include <iostream>
#include "Enums.h"

USING_NS_CC;

Meteor::Meteor()
{
    visibleSize = Director::getInstance()->getVisibleSize();
}

Meteor* Meteor::create()
{
    Meteor* pSprite = new Meteor();
    pSprite->makeResMeteors();
    auto pinfo = AutoPolygon::generatePolygon(pSprite->selectResMeteors());
    if (pSprite->initWithPolygon(pinfo))
    {
        pSprite->makePositions();
        pSprite->addEvents();
        pSprite->addPhysics();
        pSprite->initOptions();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Meteor::addEvents()
{

}

void Meteor::addPhysics()
{
    auto physicsBody = PhysicsBody::createCircle(this->getContentSize().width/2,
        // PhysicsMaterial(0.5f, 0.0f, 1)
        PHYSICSBODY_MATERIAL_DEFAULT
    );
    physicsBody->setDynamic(false);
    this->addComponent(physicsBody);
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Meteor::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void Meteor::initOptions()
{
    // this->getPhysicsBody()->setCategoryBitmask(2);
    // this->getPhysicsBody()->setCollisionBitmask(2);
    this->getPhysicsBody()->setContactTestBitmask(true);
    this->setTag(Tags::meteor);
    setPosition(selectPosition());
    makeRotation();
}

void Meteor::toMove()
{
    int timeDelay = random(1.0f, 4.0f);
    auto delay = DelayTime::create(timeDelay);
    auto toMove = MoveTo::create(5.0f + timeDelay, selectPosition());
    // this->getPhysicsBody()->applyForce(selectPosition(), 100);
    auto changeTag = CallFunc::create([this](){
        setAnimed(true);
    });
    auto seq = Sequence::create(delay, toMove, changeTag, nullptr);
    this->runAction(seq);
}

float Meteor::getHeigth()
{
    return this->getContentSize().height;
}

void Meteor::makeRotation()
{
    float time = random(2.0f, 4.0f);
    float angle = random(-360.f, 360.f);
    auto rotateBy = RotateBy::create(time, angle);
    this->runAction(
        RepeatForever::create(rotateBy)
    );
}

void Meteor::setAnimed(bool value)
{
    animed = value;
}

bool Meteor::getAnimed()
{
    return animed;
}

void Meteor::makePositions()
{
    positions.push_back(up());
    positions.push_back(down());
    positions.push_back(right());
    positions.push_back(left());
}

void Meteor::makeResMeteors()
{
    resMeteors.push_back("res/Meteors/meteorBrown_med1.png");
    resMeteors.push_back("res/Meteors/meteorBrown_med3.png");
    resMeteors.push_back("res/Meteors/meteorBrown_small1.png");
    resMeteors.push_back("res/Meteors/meteorBrown_small2.png");
    resMeteors.push_back("res/Meteors/meteorBrown_big4.png");
    resMeteors.push_back("res/Meteors/meteorGrey_med2.png");
    resMeteors.push_back("res/Meteors/meteorGrey_small2.png");
    resMeteors.push_back("res/Meteors/meteorBrown_big1.png");
    resMeteors.push_back("res/Meteors/meteorGrey_big3.png");
}

float Meteor::xMax()
{
    float width = Director::getInstance()->getVisibleSize().width;
    return width * 1.1;
}

float Meteor::xMin()
{
    float min =- getHeigth();
    return min;
}

float Meteor::yMax()
{
    float heigth = Director::getInstance()->getVisibleSize().height;
    return heigth * 1.1;
}

float Meteor::yMin()
{
    float min =- getHeigth();
    return min;
}

float Meteor::xRand()
{
    return random(0.f, xMax());
}

float Meteor::yRand()
{
    return random(0.f, yMax());
}

Vec2 Meteor::right()
{
    return Vec2(xMax(), yRand());
}

Vec2 Meteor::left()
{
    return Vec2(xMin(), yRand());
}

Vec2 Meteor::up()
{
    return Vec2(xRand(), yMax());
}

Vec2 Meteor::down()
{
    return Vec2(xRand(), yMin());
}

std::string Meteor::selectResMeteors(void)
{
    int raffle = rand() % resMeteors.size();
    return resMeteors[raffle];
}

Vec2 Meteor::selectPosition(void)
{
    int raffle = rand() % positions.size();
    Vec2 selected = positions[raffle];
    positions.erase(positions.begin() + raffle);
    return positions[raffle];
}

bool Meteor::onContactBegin(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    if(nodeA->getTag()==Tags::aircraft){
        if(nodeB->getTag()==Tags::meteor){
            return true;
        }
    }
    if(nodeA->getTag()==Tags::meteor){
        if(nodeB->getTag()==Tags::aircraft){
            return true;
        }
        if(nodeB->getTag()==Tags::meteor){
            return true;
        }
    }
    return false;
}
