//
// Created by leahycarlos21 on 4/11/18.
//

#include "Grafo.h"

bool Grafo::addVertice(int fila, int columna) {
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices.at(i).columna == columna
            && vertices.at(i).fila == fila) {
            return false;
        }
    }
    this->vertices.push_back(VerticePrim(fila, columna, 0));
    num++;
    return true;
}

bool Grafo::addArista(int fila, int columna, int filaAdy, int columnaAdy) {
    VerticePrim aux;
    VerticePrim auxAdy;
    for (int i = 0; i < this->vertices.size(); i++) {
        aux = vertices.at(i);
        if (aux.fila == fila && aux.columna == columna) {
            for (int m = 0; m < aux.arista->size(); m++) {
                auxAdy = aux.arista->at(m);
                if (auxAdy.columna == columnaAdy
                    && auxAdy.fila == filaAdy)
                    return false;
            }
        }
    }
    auxAdy = this->getVertice(filaAdy, columnaAdy);
    aux = this->getVertice(fila, columna);
    aux.arista->push_back(auxAdy);
    return true;
}

VerticePrim Grafo::getVertice(int fila, int columna) {
    VerticePrim temp;
    for (int i = 0; i < vertices.size(); i++) {
        temp = vertices.at(i);
        if (temp.fila == fila && temp.columna == columna) {
            return temp;
        }
    }
}

void Grafo::mostrarGrafo() {
    VerticePrim temp;
    VerticePrim temp2;
    for (int i = 0; i < vertices.size(); i++) {
        temp = vertices.at(i);
        cout << "El vertice (" << temp.fila << ", " << temp.columna << ")" << endl;
        for (int j = 0; j < temp.arista->size(); j++) {
            temp2 = temp.arista->at(j);
            cout << "(" << temp2.fila << ", " << temp2.columna << ") -> ";
        }
        cout << endl;
    }
}