//
// Created by leahycarlos21 on 4/11/18.
//

#ifndef LEAGUEOFGEMS_PRIMSOLVER_H
#define LEAGUEOFGEMS_PRIMSOLVER_H

#include <iostream>
#include <vector>
#include "Grafo.h"
#include "Heap.h"

using namespace std;

struct finalPath{
    int fila, columnna, prevFila, prevComlumna;
    finalPath(){

    }
    finalPath(int fila, int columna, int prevFila, int prevColumna){
        this->columnna=columna;
        this->fila=fila;
        this->prevComlumna=prevColumna;
        this->prevFila=prevFila;
    }
};



class PrimSolver {
private:
    Grafo grafo;
    vector<Vertice> visitados;
    bool isVisitado(Vertice vertice);
    Heap<pair<int,int>> pilaGenerador(int fila, int columna, int objFila, int objColumna, vector<finalPath> heapis);
    finalPath encontrarPrevPath(int prevFila, int prevColumna, vector<finalPath> path);

public:
    Heap<pair<int, int>> prim(int columnaActual, int filaActual, int objColumna, int objFila, Grafo grafis);


};


#endif //LEAGUEOFGEMS_PRIMSOLVER_H
