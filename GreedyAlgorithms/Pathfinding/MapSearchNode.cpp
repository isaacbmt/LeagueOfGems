//
// Created by leahycarlos21 on 28/10/18.
//

#include "MapSearchNode.h"
#include "globalArray.h"


int MapSearchNode::GetMap(int x, int y) {
    if (x < 0 ||
        x >= global::MAP_WIDTH ||
        y < 0 ||
        y >= global::MAP_HEIGHT
            ) {
        return 9;
    }

    return global::world_map[(y * global::MAP_WIDTH) + x];
}

bool MapSearchNode::IsSameState(MapSearchNode &rhs) {
    if ((x == rhs.x) && (y == rhs.y)) {
        return true;
    } else {
        return false;
    }




}

void MapSearchNode::PrintNodeInfo() {


    global::positions.push_back(coordinate(x, y));
}


///La funcion heuristica estima la distancia del nodo al objetivo
float MapSearchNode::GoalDistanceEstimate(MapSearchNode &nodeGoal) {
    return abs(x - nodeGoal.x) + abs(y - nodeGoal.y);
}

bool MapSearchNode::IsGoal(MapSearchNode &nodeGoal) {
    if ((x == nodeGoal.x) &&
        (y == nodeGoal.y)) {
        return true;
    }
    return false;
}

bool MapSearchNode::GetSuccessors(AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node) {

    int parent_x = -1;
    int parent_y = -1;

    if (parent_node) {
        parent_x = parent_node->x;
        parent_y = parent_node->y;
    }
    MapSearchNode NewNode;
    if ((GetMap(x - 1, y) < 9)
        && !((parent_x == x - 1) && (parent_y == y))
            ) {
        NewNode = MapSearchNode(x - 1, y);
        astarsearch->AddSuccessor(NewNode);
    }

    if ((GetMap(x, y - 1) < 9)
        && !((parent_x == x) && (parent_y == y - 1))
            ) {
        NewNode = MapSearchNode(x, y - 1);
        astarsearch->AddSuccessor(NewNode);
    }

    if ((GetMap(x + 1, y) < 9)
        && !((parent_x == x + 1) && (parent_y == y))
            ) {
        NewNode = MapSearchNode(x + 1, y);
        astarsearch->AddSuccessor(NewNode);
    }
    if ((GetMap(x, y + 1) < 9)
        && !((parent_x == x) && (parent_y == y + 1))
            ) {
        NewNode = MapSearchNode(x, y + 1);
        astarsearch->AddSuccessor(NewNode);
    }

    return true;
}

float MapSearchNode::GetCost(MapSearchNode &successor) {
    return (float) GetMap(x, y);

}


