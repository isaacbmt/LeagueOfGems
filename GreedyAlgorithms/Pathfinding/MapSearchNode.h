

#ifndef PATHFINDING_MAPSEARCHNODE_H
#define PATHFINDING_MAPSEARCHNODE_H

#include <iostream>
#include <stdio.h>
#include <math.h>
#include "AStarSearch.h"
#include "coordinate.h"

using namespace std;

class MapSearchNode {
public:

    int x;
    int y;
    /// vector<coordinate> coordenadas;


    MapSearchNode() { x = y = 0; }

    MapSearchNode(int px, int py) {
        x = px;
        y = py;
    }

    int GetMap(int x, int y);

    float GoalDistanceEstimate(MapSearchNode &nodeGoal);

    bool IsGoal(MapSearchNode &nodeGoal);

    bool GetSuccessors(AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node);

    float GetCost(MapSearchNode &successor);

    bool IsSameState(MapSearchNode &rhs);

    void PrintNodeInfo();

    const int *getWorld_map() const;
};

#endif
