#pragma once
#include "raylib.h"

class AnimData
{
public:    
    Rectangle sourceRec;
    Rectangle screenRec;
    Vector2 pos;
    int hurtPower;
    int frame;
    float updateTime;
    float runningTime;
    bool isCollided;
    bool isPassed;
};
