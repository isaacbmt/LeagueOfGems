//
// Created by leahycarlos21 on 4/11/18.
//

#ifndef LEAGUEOFGEMS_GRAFO_H
#define LEAGUEOFGEMS_GRAFO_H


#include <bits/stdc++.h>
#include <iostream>

using namespace std;

struct Vertice {
    int fila, columna, peso = 0;
    vector<Vertice> *arista;
    Vertice() = default;
    Vertice(int fila, int columna, int peso) {
        this->fila = fila;
        this->columna = columna;
        this->peso = peso;
        arista = new vector<Vertice>();
    }
};


class Grafo {
public:
    vector<Vertice> vertices;
    int num = 0;
    bool addVertice(int fila, int columna);
    bool addArista(int fila, int columna, int filaAdy, int columnaAdy);
    Vertice getVertice(int fila, int columna);
    void mostrarGrafo();
};
#endif //LEAGUEOFGEMS_GRAFO_H
