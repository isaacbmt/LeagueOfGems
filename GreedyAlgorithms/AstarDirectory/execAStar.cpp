//
// Created by leahycarlos21 on 28/10/18.
//

#include "execAStar.h"
#include "globalArray.h"


void execAStar::solution(MapSearchNode nodeStart, MapSearchNode nodeEnd) {


    AStarSearch<MapSearchNode> astarsearch;

    unsigned int SearchCount = 0;
    const unsigned int NumSearches = 1;
    while (SearchCount < NumSearches) {
        astarsearch.SetStartAndGoalStates(nodeStart, nodeEnd);

        unsigned int SearchState;
        unsigned int SearchSteps = 0;

        do {
            SearchState = astarsearch.SearchStep();

            SearchSteps++;


        } while (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING);

        if (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED) {
            cout << "Search found goal state\n";

            MapSearchNode *node = astarsearch.GetSolutionStart();

            int steps = 0;

            node->PrintNodeInfo();
            for (;;) {
                node = astarsearch.GetSolutionNext();

                if (!node) {
                    break;
                }

                node->PrintNodeInfo();
                steps++;

            };

            cout << "Solution steps " << steps << endl;
            astarsearch.FreeSolutionNodes();

        } else if (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED) {
            cout << "Search terminated. Did not find goal state\n";

        }

        cout << "SearchSteps : " << SearchSteps << "\n";
        SearchCount++;
    }

}

vector<coordinate> execAStar::obtenerCoordenadas(int matrizInterfaz[21][27], MapSearchNode nodoStart,
                                                 MapSearchNode nodoEnd) {

///Convierta de int[][] a int[] para realizar los calculos de *AStar
    int pos = 0;
    for (int y = 0; y < global::MAP_HEIGHT; y++) {
        for (int x = 0; x < global::MAP_WIDTH; x++) {
            if (matrizInterfaz[y][x] == 0) {
                matrizInterfaz[y][x] = 1;
            } else if (matrizInterfaz[y][x] == 1 || matrizInterfaz[y][x] == 3) {
                matrizInterfaz[y][x] = 9;
            }
            global::world_map[pos] = matrizInterfaz[y][x];

            pos++;
        }
    }
    ///clase del ejecutable del *AStar
    execAStar ejecutable;

    ejecutable.solution(nodoStart, nodoEnd);

    for (int y = 0; y < global::MAP_HEIGHT; y++) {
        for (int x = 0; x < global::MAP_WIDTH; x++) {
            if (matrizInterfaz[y][x] == 1) {
                matrizInterfaz[y][x] = 0;
            } else if (matrizInterfaz[y][x] == 9) {
                matrizInterfaz[y][x] = 1;
            }
        }
    }

    vector<coordinate> path = global::positions;
    global::positions.clear();

    return path;
}