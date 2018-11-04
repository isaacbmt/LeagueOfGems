//
// Created by luisk on 02/11/18.
//

#ifndef LEAGUEOFGEMS_KRUSKAL_H
#define LEAGUEOFGEMS_KRUSKAL_H

#include <iostream>
#include <stdio.h>
#include <vector>
#define ColumnasMapa 27
#define FilasMapa 21

const double SinAristaMinimaDefinida = 100000.0;
const double Arista = 1.0;

using namespace std;


struct Nodo{
    double distancia;
    int posicionX;
    int posicionY;
};

class Kruskal {
private:
    vector <Nodo> vertices[FilasMapa * ColumnasMapa];
    vector<Nodo> ruta[1];
    int contador = 0;

    bool definirRaiz(int x, int y);

    bool verificarDestino(int x, int y);

    bool revisarAristasSalientes(int posicionX, int posicionY, double peso, int destX, int destY);

    Nodo elegirAristaMenor(int posicionX, int posicionY, double peso);

    void definirRutaOptima(int x, int y);

public:
    Kruskal(int mapa[FilasMapa][ColumnasMapa]);

    Kruskal(){}

    void setMap(int mapa[FilasMapa][ColumnasMapa]);

    //Este metodo se pone donde se ponia definirPesos(int x, int y) y definirRutaOptima(int x, int y);
    void definirCamino(int xDest, int yDest, int xPlayer, int yPlayer);

    Nodo obtenerSiguienteVertice();

};


#endif //LEAGUEOFGEMS_KRUSKAL_H
