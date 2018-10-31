/**
 * Gracias a  Justin Heyes-Jones , a continuación el repositorio utilizado
 * https://github.com/justinhj/astar-algorithm-cpp
 */
#ifndef PATHFINDING_ASTARSEARCH_H
#define PATHFINDING_ASTARSEARCH_H

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <algorithm>
#include <set>
#include <vector>
#include <cfloat>

using namespace std;

template<class T>
class AStarState;

template<typename UserState>///Estado del usuario del tipo de espacio
class AStarSearch {

public:
    enum {
        SEARCH_STATE_NOT_INITIALISED,
        SEARCH_STATE_SEARCHING,
        SEARCH_STATE_SUCCEEDED,
        SEARCH_STATE_FAILED,
        SEARCH_STATE_OUT_OF_MEMORY,
        SEARCH_STATE_INVALID
    };

    class nodoStar {
    public:
        nodoStar *parent;/// Almacena el nodo padre de las sucesiones
        nodoStar *child;

        float g; ///Costo del nodo y la de su predecesor
        float h; ///estimacion heuristica de la distancia al objetivo
        float f; ///Suma acumulativa del costo de los predecesores,

        nodoStar() {
            parent = nullptr;
            child = nullptr;
            g = 0.0f;
            h = 0.0f;
            f = 0.0f;
        }

        UserState m_UserState;

    };

    class HeapCompare_f {
    public:
        bool operator()(const nodoStar *x, const nodoStar *y) const {
            return x->f > y->f;
        }
    };

    ///Metodos
    AStarSearch() :
            m_State(SEARCH_STATE_NOT_INITIALISED),
            nodoSolution(NULL),
            m_AllocateNodeCount(0),
            m_CancelRequest(false) {
    }

    AStarSearch(int MaxNodes) :
            m_State(SEARCH_STATE_NOT_INITIALISED),
            nodoSolution(NULL),

            m_AllocateNodeCount(0),
            m_CancelRequest(false) {
    }

    void cancelSearch() {
        m_CancelRequest = true;
    }

    void SetStartAndGoalStates(UserState &Start, UserState &Goal) {
        m_CancelRequest = false;

        nodoStart = AllocateNode();
        nodoObjective = AllocateNode();

        assert((nodoStart != NULL && nodoObjective != NULL));

        nodoStart->m_UserState = Start;
        nodoObjective->m_UserState = Goal;

        m_State = SEARCH_STATE_SEARCHING;

        nodoStart->g = 0;
        nodoStart->h = nodoStart->m_UserState.GoalDistanceEstimate(nodoObjective->m_UserState);
        nodoStart->f = nodoStart->g + nodoStart->h;
        nodoStart->parent = 0;

        m_OpenList.push_back(nodoStart);

        push_heap(m_OpenList.begin(), m_OpenList.end(), HeapCompare_f());


        countStep = 0;
    }


    unsigned int SearchStep() {
        assert((m_State > SEARCH_STATE_NOT_INITIALISED) &&
               (m_State < SEARCH_STATE_INVALID));

        if ((m_State == SEARCH_STATE_SUCCEEDED) ||
            (m_State == SEARCH_STATE_FAILED)
                ) {
            return m_State;
        }

        if (m_OpenList.empty() || m_CancelRequest) {
            FreeAllNodes();
            m_State = SEARCH_STATE_FAILED;
            return m_State;
        }

        countStep++;

        nodoStar *n = m_OpenList.front(); // get pointer to the node
        pop_heap(m_OpenList.begin(), m_OpenList.end(), HeapCompare_f());
        m_OpenList.pop_back();

        if (n->m_UserState.IsGoal(nodoObjective->m_UserState)) {

            nodoObjective->parent = n->parent;
            nodoObjective->g = n->g;
            if (false == n->m_UserState.IsSameState(nodoStart->m_UserState)) {
                FreeNode(n);

                nodoStar *nodeChild = nodoObjective;
                nodoStar *nodeParent = nodoObjective->parent;

                do {
                    nodeParent->child = nodeChild;

                    nodeChild = nodeParent;
                    nodeParent = nodeParent->parent;

                } while (nodeChild != nodoStart);

            }

            FreeUnusedNodes();

            m_State = SEARCH_STATE_SUCCEEDED;

            return m_State;
        } else
        {

            m_Successors.clear();

            bool ret = n->m_UserState.GetSuccessors(this, n->parent ? &n->parent->m_UserState : NULL);

            if (!ret) {

                typename vector<nodoStar *>::iterator successor;

                for (successor = m_Successors.begin(); successor != m_Successors.end(); successor++) {
                    FreeNode((*successor));
                }

                m_Successors.clear();

                FreeNode((n));
                FreeAllNodes();

                m_State = SEARCH_STATE_OUT_OF_MEMORY;
                return m_State;
            }

            for (typename vector<nodoStar *>::iterator successor = m_Successors.begin();
                 successor != m_Successors.end(); successor++) {


                float newg = n->g + n->m_UserState.GetCost((*successor)->m_UserState);

                typename vector<nodoStar *>::iterator openlist_result;

                for (openlist_result = m_OpenList.begin(); openlist_result != m_OpenList.end(); openlist_result++) {
                    if ((*openlist_result)->m_UserState.IsSameState((*successor)->m_UserState)) {
                        break;
                    }
                }

                if (openlist_result != m_OpenList.end()) {


                    if ((*openlist_result)->g <= newg) {
                        FreeNode((*successor));

                        continue;
                    }
                }

                typename vector<nodoStar *>::iterator closedlist_result;

                for (closedlist_result = m_ClosedList.begin();
                     closedlist_result != m_ClosedList.end(); closedlist_result++) {
                    if ((*closedlist_result)->m_UserState.IsSameState((*successor)->m_UserState)) {
                        break;
                    }
                }

                if (closedlist_result != m_ClosedList.end()) {


                    if ((*closedlist_result)->g <= newg) {
                        FreeNode((*successor));

                        continue;
                    }
                }

                (*successor)->parent = n;
                (*successor)->g = newg;
                (*successor)->h = (*successor)->m_UserState.GoalDistanceEstimate(nodoObjective->m_UserState);
                (*successor)->f = (*successor)->g + (*successor)->h;

                if (closedlist_result != m_ClosedList.end()) {

                    (*closedlist_result)->parent = (*successor)->parent;
                    (*closedlist_result)->g = (*successor)->g;
                    (*closedlist_result)->h = (*successor)->h;
                    (*closedlist_result)->f = (*successor)->f;


                    FreeNode((*successor));

                    m_OpenList.push_back((*closedlist_result));

                    m_ClosedList.erase(closedlist_result);
                    push_heap(m_OpenList.begin(), m_OpenList.end(), HeapCompare_f());

                } else if (openlist_result != m_OpenList.end()) {
                    (*openlist_result)->parent = (*successor)->parent;
                    (*openlist_result)->g = (*successor)->g;
                    (*openlist_result)->h = (*successor)->h;
                    (*openlist_result)->f = (*successor)->f;
                    FreeNode((*successor));
                    make_heap(m_OpenList.begin(), m_OpenList.end(), HeapCompare_f());
                } else {
                    m_OpenList.push_back((*successor));
                    push_heap(m_OpenList.begin(), m_OpenList.end(), HeapCompare_f());
                }
            }
            m_ClosedList.push_back(n);

        }

        return m_State;

    }

    bool AddSuccessor(UserState &State) {
        nodoStar *node = AllocateNode();

        if (node) {
            node->m_UserState = State;

            m_Successors.push_back(node);

            return true;
        }

        return false;
    }

    void FreeSolutionNodes() {
        nodoStar *n = nodoStart;

        if (nodoStart->child) {
            do {
                nodoStar *del = n;
                n = n->child;
                FreeNode(del);

                del = NULL;

            } while (n != nodoObjective);

            FreeNode(n);

        } else {
            FreeNode(nodoStart);
            FreeNode(nodoObjective);
        }

    }


    UserState *GetSolutionStart() {
        nodoSolution = nodoStart;
        if (nodoStart) {
            return &nodoStart->m_UserState;
        } else {
            return NULL;
        }
    }


    UserState *GetSolutionNext() {
        if (nodoSolution) {
            if (nodoSolution->child) {

                nodoStar *child = nodoSolution->child;

                nodoSolution = nodoSolution->child;

                return &child->m_UserState;
            }
        }

        return NULL;
    }

    void FreeAllNodes() {
        typename vector<nodoStar *>::iterator iterOpen = m_OpenList.begin();

        while (iterOpen != m_OpenList.end()) {
            nodoStar *n = (*iterOpen);
            FreeNode(n);

            iterOpen++;
        }

        m_OpenList.clear();
        typename vector<nodoStar *>::iterator iterClosed;

        for (iterClosed = m_ClosedList.begin(); iterClosed != m_ClosedList.end(); iterClosed++) {
            nodoStar *n = (*iterClosed);
            FreeNode(n);
        }
        m_ClosedList.clear();
        FreeNode(nodoObjective);
    }

    void FreeUnusedNodes() {
        typename vector<nodoStar *>::iterator iterOpen = m_OpenList.begin();

        while (iterOpen != m_OpenList.end()) {
            nodoStar *n = (*iterOpen);

            if (!n->child) {
                FreeNode(n);

                n = NULL;
            }

            iterOpen++;
        }

        m_OpenList.clear();
        typename vector<nodoStar *>::iterator iterClosed;

        for (iterClosed = m_ClosedList.begin(); iterClosed != m_ClosedList.end(); iterClosed++) {
            nodoStar *n = (*iterClosed);

            if (!n->child) {
                FreeNode(n);
                n = NULL;

            }
        }

        m_ClosedList.clear();

    }

    nodoStar *AllocateNode() {

        m_AllocateNodeCount++;
        nodoStar *p = new nodoStar;
        return p;
    }

    void FreeNode(nodoStar *node) {
        m_AllocateNodeCount--;

        delete node;

    }

    ///--------------Atributos--------------
    vector<nodoStar *> m_OpenList;
    vector<nodoStar *> m_ClosedList;
    vector<nodoStar *> m_Successors;
    unsigned int m_State;
    int countStep;
    nodoStar *nodoStart;
    nodoStar *nodoObjective;
    nodoStar *nodoSolution;
    int m_AllocateNodeCount;
    bool m_CancelRequest;

};

#endif //PATHFINDING_ASTARSEARCH_H
