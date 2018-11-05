//
// Created by leahycarlos21 on 4/11/18.
//

#ifndef LEAGUEOFGEMS_GRAFO_H
#define LEAGUEOFGEMS_GRAFO_H


#include <bits/stdc++.h>
#include <iostream>

using namespace std;

struct VerticePrim {
    int fila, columna, peso = 0;
    vector<VerticePrim> *arista;
    VerticePrim() = default;
    VerticePrim(int fila, int columna, int peso) {
        this->fila = fila;
        this->columna = columna;
        this->peso = peso;
        arista = new vector<VerticePrim>();
    }
};


class Grafo {
public:
    vector<VerticePrim> vertices;
    int num = 0;
    bool addVertice(int fila, int columna);
    bool addArista(int fila, int columna, int filaAdy, int columnaAdy);
    VerticePrim getVertice(int fila, int columna);
    void mostrarGrafo();
};


#endif //LEAGUEOFGEMS_GRAFO_H
