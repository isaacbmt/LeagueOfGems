//
// Created by leahycarlos21 on 3/11/18.
//

#include "generadorGrafo.h"

Grafo generadorGrafo::generarGrafo(int matrix[defFilas][defColas]) {
    ///Filas i
    for (int i = 0; i < defFilas; i++) {
        ///Columna j
        for (int j = 0; j < defColas; j++) {
            if (isPermitido(i, j, matrix)) {
                grafo.addVertice(i, j);

                if (isPermitido(i + 1, j, matrix)) {
                    grafo.addVertice(i + 1, j);
                    grafo.addArista(i, j, i + 1, j);

                }
                if (isPermitido(i - 1, j, matrix)) {
                    grafo.addVertice(i - 1, j);
                    grafo.addArista(i, j, i - 1, j);

                }
                if (isPermitido(i, j + 1, matrix)) {
                    grafo.addVertice(i, j + 1);
                    grafo.addArista(i, j, i, j + 1);
                }
                if (isPermitido(i, j - 1, matrix)) {
                    grafo.addVertice(i, j - 1);
                    grafo.addArista(i, j, i, j - 1);

                }
            }
        }
    }
    return this->grafo;
}

bool generadorGrafo::isPermitido(int fila, int columna, int matrix[defFilas][defColas]) {
    return fila >= 0 && fila < defFilas && columna >= 0 && columna < defColas && matrix[fila][columna] == 1;

}