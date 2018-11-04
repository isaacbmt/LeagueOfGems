//AGREGADO POR GABRIEL

#ifndef LEAGUEOFGEMS_ALGORITMOGEN_H
#define LEAGUEOFGEMS_ALGORITMOGEN_H


#include "LinkedListGen.h"
#include <iostream>
#include<stdlib.h> //Esto es para generar numeros random
#include<time.h> //Esto es para generar numeros random
#include <iostream>
#include <random>



class AlgoritmoGen {


private:

    LinkedListGen<LinkedListGen<int>> *oleada;
    LinkedListGen<LinkedListGen<int>> *oleada_copia;
    LinkedListGen<LinkedListGen<LinkedListGen<int>>> *ListaOleadas;
    int fitness;


public:

    /**
     * Constructor
     */

    AlgoritmoGen() {

        oleada = new LinkedListGen<LinkedListGen<int>>();
        oleada_copia = new LinkedListGen<LinkedListGen<int>>();
        ListaOleadas = new LinkedListGen<LinkedListGen<LinkedListGen<int>>>();
        fitness = 0;
    }



    /**
     * CreaOleadas
     * @return
     */
    LinkedListGen<LinkedListGen<LinkedListGen<int>>> CreaOleadas(int dificultad) {

        srand(time(NULL));

        if (dificultad==1){
            for(int i=0;i<5;i++){
                oleada->add(Crea_ListaEnemigos());
            }
            for (int i=0;i<oleada->length();i++){
                oleada_copia->add(oleada->get(i));
            }
            fitness = suma_caracteristicas(*SeleccionaMejores(*oleada));
            ListaOleadas->add(*oleada);

            while (fitness < 50) {
                ListaOleadas->add(CambiaPeor(*oleada_copia));
                fitness = suma_caracteristicas(*SeleccionaMejores(*oleada_copia));
            }
        }
        else if (dificultad==2){
            for(int i=0;i<10;i++){
                oleada->add(Crea_ListaEnemigos());
            }
            for (int i=0;i<oleada->length();i++){
                oleada_copia->add(oleada->get(i));
            }
            fitness = suma_caracteristicas(*SeleccionaMejores(*oleada));
            ListaOleadas->add(*oleada);

            while (fitness < 100) {
                ListaOleadas->add(CambiaPeor(*oleada_copia));
                fitness = suma_caracteristicas(*SeleccionaMejores(*oleada_copia));
            }
        }
        else{
            for(int i=0;i<20;i++){
                oleada->add(Crea_ListaEnemigos());
            }
            for (int i=0;i<oleada->length();i++){
                oleada_copia->add(oleada->get(i));
            }
            fitness = suma_caracteristicas(*SeleccionaMejores(*oleada));
            ListaOleadas->add(*oleada);

            while (fitness < 200) {
                ListaOleadas->add(CambiaPeor(*oleada_copia));
                fitness = suma_caracteristicas(*SeleccionaMejores(*oleada_copia));
            }
        }

        Imprimir_lista_Pro3(*ListaOleadas);
        std::cout << fitness << std::endl;
        return *ListaOleadas;
    }


    /**
     * SeleccionaMejores
     * @param lista
     * @return
     */
    LinkedListGen<int>* SeleccionaMejores(LinkedListGen<LinkedListGen<int>> lista) {
        int velocidad = 0;
        int fuerza = 0;
        int alcance = 0;
        int vida = 0;
        LinkedListGen<int> *resultado = new LinkedListGen<int>();

        for (int i = 0; i < lista.length(); i++) {
            if (velocidad < lista.get(i).get(0)) {
                velocidad = lista.get(i).get(0);
            }
            if (fuerza < lista.get(i).get(1)) {
                fuerza = lista.get(i).get(1);
            }
            if (alcance < lista.get(i).get(2)) {
                alcance = lista.get(i).get(2);
            }
            if (vida < lista.get(i).get(3)) {
                vida = lista.get(i).get(3);
            }
        }
        resultado->add(velocidad);
        resultado->add(fuerza);
        resultado->add(alcance);
        resultado->add(vida);
        return (resultado);
    }



    /**
   * CambiaPeor
   * @param lista
   * @return
   */
    LinkedListGen<LinkedListGen<int>> CambiaPeor(LinkedListGen<LinkedListGen<int>> lista) {

        LinkedListGen<LinkedListGen<int>> resultado_final;
        LinkedListGen<int> resultado;
        int posicion_a_borrar=0;

        resultado.add(10);
        resultado.add(10);
        resultado.add(10);
        resultado.add(10);

        for (int i = 0; i < oleada_copia->length(); i++) {
            if (suma_caracteristicas(oleada_copia->get(i))<suma_caracteristicas(resultado)){
                resultado = oleada_copia->get(i);
                posicion_a_borrar=i;
            }
        }

        oleada_copia->set_Data(posicion_a_borrar,*Mutaciones(*SeleccionaMejores(*oleada_copia)));

        for (int i=0;i<oleada_copia->length();i++){
            resultado_final.add(oleada_copia->get(i));
        }
        return resultado_final ;
    }


    /**
     * suma_caracteristicas
     * @param lista
     * @return
     */
    int suma_caracteristicas(LinkedListGen<int> lista) {
        int a = 0;
        for (int i = 0; i < lista.length(); i++) {
            a += lista.get(i);
        }
        return a;
    }

    /**
     *
     * @param lista
     * @return
     */
    LinkedListGen<int>* Mutaciones(LinkedListGen<int> lista) {

        LinkedListGen<int> *lista_mutados = new LinkedListGen<int>();
        for (int i = 0; i < lista.length(); i++) {
            lista_mutados->add(lista.get(i) + (1+rand()%4));
        }
        return lista_mutados;
    }

    /**
     *
     * @param lista
     */
    void Imprimir_lista_Pro3(LinkedListGen<LinkedListGen<LinkedListGen<int>>> lista) {
        for (int i = 0; i < lista.length(); i++) {
            for (int j = 0; j < lista.get(i).length(); j++) {
                std::cout << "" << std::endl;
                Imprimir_lista(lista.get(i).get(j));
                std::cout << "" << std::endl;
            }
            std::cout << "Siguiente oleada" << std::endl;
        }
    }

    /**
     *
     * @param lista
     */
    void Imprimir_listaTmp(LinkedListGen<LinkedListGen<int>> lista) {
        for (int i = 0; i < lista.length(); i++) {
            std::cout << lista.get(i).get(0) << std::endl;
            std::cout << lista.get(i).get(1) << std::endl;
            std::cout << lista.get(i).get(2) << std::endl;
            std::cout << lista.get(i).get(3) << std::endl;
            std::cout << "" << std::endl;
        }
    }

    /**
     *
     * @param lista
     */
    void Imprimir_lista(LinkedListGen<int> lista) {
        for (int i = 0; i < lista.length(); i++) {
            std::cout << lista.get(i) << std::endl;
        }
    }

    LinkedListGen<int> Crea_ListaEnemigos() {
        LinkedListGen<int> *temporal1=new LinkedListGen<int>();

        for (int i = 0; i < 4; i++) {
            temporal1->add(1+rand()% 4);
        }
        return *temporal1;
    }
};

#endif //LEAGUEOFGEMS_ALGORITMOGEN_H
