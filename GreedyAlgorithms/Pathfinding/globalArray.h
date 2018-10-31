//
// Created by leahycarlos21 on 28/10/18.
//

#ifndef PATHFINDING_GLOBALARRAY_H
#define PATHFINDING_GLOBALARRAY_H

#pragma once

#include "coordinate.h"

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>

using  namespace std;

namespace global {
    extern const int MAP_WIDTH;
    extern const int MAP_HEIGHT;
    ///Son las variables constantes que se llamaran en el analisis del *A
    extern int world_map[];
    extern vector<coordinate> positions;
}

#endif //PATHFINDING_GLOBALARRAY_H
