//
// Created by luisk on 24/10/18.
//

#include "Dijkstra.h"

bool Dijkstra::definirCentro(int x,int y){
    cout<<"Definiendo centro"<<endl;
    int xAux;
    int yAux;
    for(int i = 0; i<verticesPendientes->size(); i++) {
        yAux = (verticesPendientes->operator[](i)).posicionYtiles;
        xAux = (verticesPendientes->operator[](i)).posicionXtiles;
        if(xAux == x && yAux == y){
            (verticesPendientes->operator[](i)).distancia = 0.0;
            cout<<"Centro definido"<<endl;
            return true;
        }
    }
    cout<<"No se puede definir centro en esa posicion"<<endl;
    return false;
}

void Dijkstra::evaluarVecinos(int posicionX, int posicionY, double peso){
    double dist = 0.0;
    for(int y = posicionY-1; y <= posicionY+1; y++){
        for(int x = posicionX-1; x <= posicionX+1; x++){
            if(y < 0 || x < 0 || y > FilasMapa-1 || x > ColumnasMapa-1){
            }else if(x == posicionX && y == posicionY){
            }else{
                Vertice aux;
                for(int i = 0; i<verticesPendientes->size(); i++) {
                    aux = verticesPendientes->operator[](i);
                    if (aux.posicionXtiles == x && aux.posicionYtiles == y) {
                        if(aux.distancia == INF){
                            if(x != posicionX && y != posicionY){
                                dist = DIAGONAL;
                            }else{
                                dist = 1.0;
                            }
                            (verticesPendientes->operator[](i)).distancia = peso + dist;
                        }
                        else if(!(aux.visitado)){
                            if(x != posicionX && y != posicionY){
                                dist = DIAGONAL;
                            }else{
                                dist = 1.0;
                            }
                            if(peso + dist < aux.distancia) {
                                (verticesPendientes->operator[](i)).distancia = peso + dist;
                            }
                        }else{

                        }
                    }
                }
            }
        }
    }
}


Vertice Dijkstra::retornarVecinoMenor(int posicionX, int posicionY, double peso){
    double dist = peso;
    Vertice verticeAux1;
    Vertice verticeAux2;
    verticeAux1.distancia = peso;
    verticeAux1.posicionXtiles = posicionX;
    verticeAux1.posicionYtiles = posicionY;
    for(int y = posicionY-1; y <= posicionY+1; y++){
        for(int x = posicionX-1; x <= posicionX+1; x++){
            if(y < 0 || x < 0 || y > FilasMapa-1 || x > ColumnasMapa-1){
            }else if(x == posicionX && y == posicionY){
            }else{
                for(int i = 0; i<verticesPendientes->size(); i++) {
                    verticeAux2 = verticesPendientes->operator[](i);
                    if (verticeAux2.posicionXtiles == x && verticeAux2.posicionYtiles == y) {
                        if(verticeAux2.distancia < dist){
                            dist = verticeAux2.distancia;
                            verticeAux1 = verticeAux2;
                        }
                    }
                }
            }
        }
    }
    return verticeAux1;
}


Dijkstra::Dijkstra(int mapa[FilasMapa][ColumnasMapa]){
    for (int y = 0; y < FilasMapa; y++){
        for (int x = 0; x < ColumnasMapa; x++){
            if(mapa[y][x] == 0) {
                Vertice vertice;
                vertice.distancia = INF;
                vertice.posicionXtiles = x;
                vertice.posicionYtiles = y;
                vertice.visitado = false;
                verticesMapa->push_back(vertice);
            }
        }
    }
}

void Dijkstra::definirPesos(int x, int y){
    if(y<FilasMapa && x<ColumnasMapa){
        verticesPendientes->clear();
        for(int i = 0; i<verticesMapa->size(); i++) {
            verticesPendientes->push_back(verticesMapa->operator[](i));
        }
        if(definirCentro(x,y)) {
            Vertice aux;
            for(int i = 0; i < 25; i++) {
                for (int i = 0; i < verticesPendientes->size(); i++) {
                    aux = verticesPendientes->operator[](i);
                    if (aux.distancia != INF) {
                        evaluarVecinos(aux.posicionXtiles, aux.posicionYtiles, aux.distancia);
                        (verticesPendientes->operator[](i)).visitado = true;
                    }
                }
            }
        }
    }
}

void Dijkstra::definirRutaOptima(int x, int y) {
    if (y < FilasMapa && x < ColumnasMapa) {
        int xAux;
        int yAux;
        Vertice verticeActual;
        Vertice vertAux;
        verticeActual.distancia = INF;
        ruta->clear();
        contador = 0;

        for (int i = 0; i < verticesPendientes->size(); i++) {
            vertAux = verticesPendientes->operator[](i);
            yAux = vertAux.posicionYtiles;
            xAux = vertAux.posicionXtiles;
            if (xAux == x && yAux == y) {
                verticeActual = vertAux;
                break;
            }
        }

        if (verticeActual.distancia == INF) {
            cout << "Fuera de rango" << endl;
        } else if (verticeActual.distancia == 0.0) {
            ruta->push_back(verticeActual);
        } else {
            ruta->push_back(verticeActual);
            bool flag = true;
            while (flag) {
                verticeActual = retornarVecinoMenor(verticeActual.posicionXtiles,
                                                    verticeActual.posicionYtiles, verticeActual.distancia);
                if (verticeActual.distancia == 0.0) {
                    ruta->push_back(verticeActual);
                    flag = false;
                } else {
                    ruta->push_back(verticeActual);
                }
            }
        }

        cout << "{" << endl;
        for (int i = 0; i < ruta->size(); i++) {
            cout << "(Vertice" << i << ": X = " << (ruta->operator[](i)).posicionXtiles << "," << "Y = "
                 << (ruta->operator[](i)).posicionYtiles << ", Peso = " << (ruta->operator[](i)).distancia << "),"
                 << endl;
        }
        cout << "}" << endl;
    }
}

Vertice Dijkstra::obtenerSiguienteVertice(){
    Vertice aux;
    aux.posicionXtiles = -1;
    aux.posicionYtiles = -1;
    if(contador < ruta->size()){
        aux = ruta->operator[](contador);
    }
    contador++;
    return aux;
}
