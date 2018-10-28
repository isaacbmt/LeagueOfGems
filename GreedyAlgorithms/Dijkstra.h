//
// Created by luisk on 24/10/18.
//

#ifndef LEAGUEOFGEMS_DIJKSTRA_H
#define LEAGUEOFGEMS_DIJKSTRA_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#define ColumnasMapa 27
#define FilasMapa 21

const double INF = 99999.0;
const double DIAGONAL = 1.42412;

using namespace std;

struct Vertice{
    double distancia;
    int posicionXtiles;
    int posicionYtiles;
    bool visitado;
};

class Dijkstra {
private:
    vector<Vertice> verticesMapa[FilasMapa*ColumnasMapa];
    vector<Vertice> verticesPendientes[FilasMapa*ColumnasMapa];
    vector<Vertice> ruta[1];
    int contador = 0;

    bool definirCentro(int x,int y);

    void evaluarVecinos(int posicionX, int posicionY, double peso);

    Vertice retornarVecinoMenor(int posicionX, int posicionY, double peso);



public:
    Dijkstra(int mapa[FilasMapa][ColumnasMapa]);

    Dijkstra(){}

    void definirPesos(int x, int y);

    void definirRutaOptima(int x, int y);

    Vertice obtenerSiguienteVertice();

};


#endif //LEAGUEOFGEMS_DIJKSTRA_H
