#pragma once

#include <iostream>
#include "Position.h"
#include "Scene.h"
#include "Map.h"
#include "Enum.h"

class Player
{
public:
    Player(Scene *scene, Position pos);

    Position pos;

private:
    Scene* scene;
};