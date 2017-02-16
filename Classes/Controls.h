#ifndef __CONTROLS_H__
#define __CONTROLS_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <vector>
#include <string>
#include <algorithm>

class Aircraft;

class Controls
{
public:
    Controls(Aircraft *aircraft);
    bool isPressed(std::string item);
private:
    void addControls();
    bool remove(std::string item);

    cocos2d::ui::Button* make(const std::string& resource, const std::string& name);
    cocos2d::Size visibleSize;
    cocos2d::ui::Button* left;
    cocos2d::ui::Button* up;
    cocos2d::ui::Button* right;
    cocos2d::ui::Button* down;
    cocos2d::ui::Button* laser;
    cocos2d::Scene* scene;
    std::vector<std::string> controls;
    Aircraft *aircraft;
};
#endif // __CONTROLS_H__
