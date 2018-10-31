//
// Created by leahycarlos21 on 28/10/18.
//

#include "execAStar.h"


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
