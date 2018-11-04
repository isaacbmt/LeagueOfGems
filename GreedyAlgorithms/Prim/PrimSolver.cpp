//
// Created by leahycarlos21 on 4/11/18.
//

#include "PrimSolver.h"

#include "PrimSolver.h"

Heap<pair<int, int>> PrimSolver::prim(int columnaActual, int filaActual, int objColumna, int objFila, Grafo grafis){
    this->grafo = grafis;
    vector<Vertice> queue;
    Vertice current = this->grafo.getVertice(filaActual, columnaActual);
    Vertice temp;
    visitados.push_back(current);

    queue.push_back(current);
    vector<finalPath> prev;
    prev.push_back(finalPath{current.fila, current.columna, -1, -1});
    while (!queue.empty()) {
        current = queue.at(0);
        queue.erase(queue.begin());
        if (current.fila == objFila && current.columna == objColumna) {

            break;
        }
        for (int i = 0; i < current.arista->size(); i++) {

            temp = current.arista->at(i);
            if (!isVisitado(temp)) {
                visitados.push_back(temp);
                temp.peso = current.peso + 1;
                queue.push_back(temp);
                prev.push_back(finalPath{temp.fila, temp.columna, current.fila, current.columna});
            }
        }
    }

    return pilaGenerador(filaActual, columnaActual, objFila, objColumna, prev);
}

bool PrimSolver::isVisitado(Vertice vertice) {
    for (int i = 0; i < visitados.size(); i++) {
        if (visitados.at(i).columna == vertice.columna && visitados.at(i).fila == vertice.fila) {
            return true;
        }
    }
    return false;
}


Heap<pair<int, int>>
PrimSolver::pilaGenerador(int fila, int columna, int objFila, int objColumna, vector<finalPath> heapis) {
    Heap<pair<int, int>> heap;
    finalPath tempPath;
    for (int i = 0; i < heapis.size(); i++) {
        if (heapis.at(i).fila == objFila && heapis.at(i).columnna == objColumna) {
            tempPath = heapis.at(i);

        }
    }

    while (true) {
        if (tempPath.fila == fila && tempPath.columnna == columna) {
            break;
        }
        heap.push(make_pair(tempPath.fila, tempPath.columnna));

        tempPath = encontrarPrevPath(tempPath.prevFila, tempPath.prevComlumna, heapis);

    }
    return heap;

}

finalPath PrimSolver::encontrarPrevPath(int prevFila, int prevColumna, vector<finalPath> path) {
    finalPath temp;
    for (int i = 0; i < path.size(); i++) {
        temp = path.at(i);
        if (temp.fila == prevFila && temp.columnna == prevColumna) {
            return temp;
        }
    }

}
