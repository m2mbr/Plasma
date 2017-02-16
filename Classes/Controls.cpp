#include "Controls.h"
#include "Aircraft.h"

USING_NS_CC;

Controls::Controls(Aircraft *aircraft)
{
    this->aircraft = aircraft;
    visibleSize = Director::getInstance()->getVisibleSize();
    addControls();
}

ui::Button* Controls::make(const std::string& resource, const std::string& name)
{
    ui::Button* btn = ui::Button::create(resource);
    btn->setTouchEnabled(true);
    btn->setName(name);
    btn->setOpacity(150);
    btn->setSwallowTouches(true);
    btn->setScale(1);
    btn->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                controls.push_back(name);
                break;
            case ui::Widget::TouchEventType::ENDED:
                remove(name);
                break;
            default:
                break;
        }
    });
    aircraft->getParent()->addChild(btn, 10);
    return btn;
}

bool Controls::isPressed(std::string item)
{
    if ( std::find(controls.begin(), controls.end(), item) != controls.end() ){
        return true;
    }
    return false;
}

bool Controls::remove(std::string item)
{
    if ( std::find(controls.begin(), controls.end(), item) != controls.end() ){
        controls.erase(
            std::remove(controls.begin(), controls.end(), item), controls.end()
        );
       return true;
    }else{
       return false;
    }
}

void Controls::addControls()
{
    laser = make("res/Controls/shadedLight49.png", "laser");
    laser->setPosition(
        Point(visibleSize.width - laser->getContentSize().width, visibleSize.height / 6.5f)
    );
    laser->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                aircraft->shotLaser();
                break;
            case ui::Widget::TouchEventType::ENDED:
                break;
            default:
                break;
        }
    });

    // left = make("res/Controls/shadedLight05.png", "left");
    // left->setPosition(
    //     Point(visibleSize.width / 7.9f, visibleSize.height / 6.5f)
    // );
    
    // right = make("res/Controls/shadedLight06.png", "right");
    // right->setPosition(
    //     Point(visibleSize.width / 5.0f, visibleSize.height / 6.5f)
    // );
    
    // up = make("res/Controls/shadedLight03.png", "up");
    // up->setPosition(
    //     Point(visibleSize.width /6.1f, visibleSize.height / 4.8f)
    // );
    
    // down = make("res/Controls/shadedLight10.png", "down");
    // down->setPosition(
    //     Point(visibleSize.width /6.1f, visibleSize.height / 9.8f)
    // );
}
