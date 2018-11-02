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
    vector<coordinate> obtenerCoordenadas(int matrizInterfaz[21][27], MapSearchNode nodoInicio,
                                                                      MapSearchNode nodoFinal);
};


#endif //PATHFINDING_EXECASTAR_H
