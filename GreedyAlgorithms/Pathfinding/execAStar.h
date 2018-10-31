//
// Created by leahycarlos21 on 28/10/18.
//

#ifndef PATHFINDING_EXECASTAR_H
#define PATHFINDING_EXECASTAR_H


#include "MapSearchNode.h"
#include "coordinate.h"

class execAStar {
public:
    MapSearchNode mapSearchNode;
    void solution(MapSearchNode nodeStart,MapSearchNode nodeEnd);
    vector<coordinate> coordenadas;

};


#endif //PATHFINDING_EXECASTAR_H
