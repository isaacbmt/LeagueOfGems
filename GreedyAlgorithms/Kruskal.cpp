//
// Created by luisk on 02/11/18.
//

#include "Kruskal.h"

bool Kruskal::definirRaiz(int x, int y){
    cout<<"Definiendo centro"<<endl;
    int size = vertices->size();
    for(int i = 0; i < size; i++) {
        if((vertices->operator[](i)).posicionX == x && (vertices->operator[](i)).posicionY == y){
            (vertices->operator[](i)).distancia = 0.0;
            cout<<"Centro definido"<<endl;
            return true;
        }
    }
    cout<<"No se puede definir centro en esa posicion"<<endl;
    return false;
}

bool Kruskal::verificarDestino(int x, int y){
    int size = vertices->size();
    for(int i = 0; i < size; i++) {
        if((vertices->operator[](i)).posicionX == x && (vertices->operator[](i)).posicionY == y){
            return true;
        }
    }
    return false;
}

bool Kruskal::revisarAristasSalientes(int posicionX, int posicionY, double peso, int destX, int destY){
    for(int y = posicionY-1; y <= posicionY+1; y++){
        for(int x = posicionX-1; x <= posicionX+1; x++){
            if(y < 0 || x < 0 || y > FilasMapa-1 || x > ColumnasMapa-1){
            }else if((x == posicionX && y == posicionY)) {
                if(x == destX && y == destY)
                    return true;
            }else{
                for(int i = 0; i < vertices->size(); i++) {
                    if ((vertices->operator[](i)).posicionX == x && (vertices->operator[](i)).posicionY == y) {
                        if((vertices->operator[](i)).distancia == SinAristaMinimaDefinida &&
                           !(x != posicionX && y != posicionY))
                        {
                            (vertices->operator[](i)).distancia = peso + Arista;
                        }
                    }
                }
            }
        }
    }
    return false;
}

Nodo Kruskal::elegirAristaMenor(int posicionX, int posicionY, double peso){
    double dist = peso;
    Nodo verticeAux;
    verticeAux.distancia = peso;
    verticeAux.posicionX = posicionX;
    verticeAux.posicionY = posicionY;
    for(int y = posicionY-1; y <= posicionY+1; y++){
        for(int x = posicionX-1; x <= posicionX+1; x++){
            if(y < 0 || x < 0 || y > FilasMapa-1 || x > ColumnasMapa-1){
            }else if(x == posicionX && y == posicionY){
            }else{
                for(int i = 0; i<vertices->size(); i++) {
                    if ((vertices->operator[](i)).posicionX == x && (vertices->operator[](i)).posicionY == y) {
                        if((vertices->operator[](i)).distancia < dist && !(x != posicionX && y != posicionY)){
                            dist = vertices->operator[](i).distancia;
                            verticeAux = vertices->operator[](i);
                        }
                    }
                }
            }
        }
    }
    return verticeAux;
}

void Kruskal::definirRutaOptima(int x, int y){
    if(y<FilasMapa && x<ColumnasMapa) {
        ruta->clear();
        Nodo verticeActual;
        verticeActual.distancia = SinAristaMinimaDefinida;

        for(int i = 0; i<vertices->size(); i++) {
            if((vertices->operator[](i)).posicionX == x && (vertices->operator[](i)).posicionY == y){
                verticeActual = (vertices->operator[](i));
                break;
            }
        }

        if(verticeActual.distancia == SinAristaMinimaDefinida){
            cout << "Fuera de rango" << endl;
        }else if (verticeActual.distancia == 0.0) {
            ruta->push_back(verticeActual);
        }else {
            ruta->push_back(verticeActual);
            bool flag = true;
            while (flag) {
                verticeActual = elegirAristaMenor(verticeActual.posicionX,
                                                  verticeActual.posicionY, verticeActual.distancia);
                if (verticeActual.distancia == 0.0) {
                    ruta->push_back(verticeActual);
                    flag = false;
                } else {
                    ruta->push_back(verticeActual);
                }
            }
        }
        contador = ruta->size()-1;
    }
}

Kruskal::Kruskal(int mapa[FilasMapa][ColumnasMapa]){

}

void Kruskal::setMap(int (*mapa)[27]) {
    vertices->clear();
    for (int y = 0; y < FilasMapa; y++){
        for (int x = 0; x < ColumnasMapa; x++){
            if(mapa[y][x] ==  0) {
                Nodo vertice;
                vertice.distancia = SinAristaMinimaDefinida;
                vertice.posicionX = x;
                vertice.posicionY = y;
                vertices->push_back(vertice);
            }
        }
    }
}

void Kruskal::definirCamino(int xDest, int yDest, int xPlayer, int yPlayer){
    if((yDest<FilasMapa && xDest<ColumnasMapa)||(yPlayer<FilasMapa && xPlayer<ColumnasMapa)){
        for(int i = 0; i<vertices->size(); i++) {
            vertices->operator[](i).distancia = SinAristaMinimaDefinida;
        }
        if(definirRaiz(xPlayer, yPlayer)) {
            bool flag = true;
            int cont = 0;
            if(verificarDestino(xDest,yDest)) {
                while (flag) {
                    if(cont > 15) {
                        flag = false;
                    }
                    for (int i = 0; i < vertices->size(); i++) {
                        if ((vertices->operator[](i)).distancia != SinAristaMinimaDefinida) {
                            if (revisarAristasSalientes((vertices->operator[](i)).posicionX,
                                                        (vertices->operator[](i)).posicionY,
                                                        (vertices->operator[](i)).distancia, xDest, yDest)) {
                                cont++;
                            }
                        }
                    }
                }
            }
        }
    }
    definirRutaOptima(xDest, yDest);
}


Nodo Kruskal::obtenerSiguienteVertice(){
    Nodo aux;
    aux.posicionX = -1;
    aux.posicionY = -1;
    if(0 <= contador){
        if(contador < ruta->size()) {
            aux = ruta->operator[](contador);
        }
    }
    contador--;
    return aux;
}