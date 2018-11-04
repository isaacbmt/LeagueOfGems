//
// Created by leahycarlos21 on 4/11/18.
//

#ifndef LEAGUEOFGEMS_GENERADORGRAFO_H
#define LEAGUEOFGEMS_GENERADORGRAFO_H



#include "Grafo.h"


class generadorGrafo {
public:
    ///Dimensiones de la matriz
    const static int defFilas = 21;
    const static int defColas = 27;
    Grafo grafo;
    Grafo generarGrafo(int matriz[defFilas][defColas]);

    bool isPermitido(int fila, int columna, int matrix[defFilas][defColas]);

};


#endif //LEAGUEOFGEMS_GENERADORGRAFO_H
