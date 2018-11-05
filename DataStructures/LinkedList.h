#ifndef LEAGUEOFGEMS_LINKEDLIST_H
#define LEAGUEOFGEMS_LINKEDLIST_H

#include "Node.h"

using namespace std;

template <class T>
class LinkedList {
public:
    /// Constructor.
    LinkedList(){
        head = nullptr;
        size = 0;
    }

    /// Adiciona un nodo a la lista.
    /// \param data El valor que va a almacenar.
    void add(T data){
        if (head == nullptr){
            head = new Node<T>(data);
            size++;
        }
        else{
            Node<T> *tmp = head;

            while(tmp->getNext() != nullptr){
                tmp = tmp->getNext();
            }
            tmp->setNext(new Node<T>(data));
            size++;
        }
    }

    /// Remueve un nodo de la lista.
    /// \param index Indice del elemento que va a eliminar.
    void remove(int index) {
        if (index == 0){
            Node<T> *tmp;
            tmp = head;
            head = head->getNext();
            size--;
            delete tmp;
            return;
        }
        else{
            Node<T> *tmp = head;
            Node<T> *tmp2;

            for (int i = 0; i < size; ++i) {
                if (i == index){
                    tmp2->setNext(tmp->getNext());
                    delete tmp;
                    size--;
                    cout << "Eliminado de la lista" << endl;
                    return;
                }
                tmp2 = tmp;
                tmp = tmp->getNext();
            }
        }
    }

    void clear() {
        Node<T> *tmp;
        for (int i = 0; i < size; ++i) {
            tmp = head;
            head = head->getNext();
            delete tmp;
        }
        size = 0;
    }

    /// Obtiene un valor de la lista.
    /// \param index Indice del elemento en la lista.
    /// \return El valor del elemento en la lista.
    T get(int index) {
        Node<T> *tmp = head;
        for (int i = 0; i < index; ++i) {
            tmp = tmp->getNext();
        }
        return tmp->getData();
    }

    /// Obtiene el largo de la lista.
    /// \return El largo de la lista.
    int length() {
        return size;
    }

    ~LinkedList(){
        head = nullptr;
    }

private:
    Node<T> *head;
    int size;
};

#endif //LEAGUEOFGEMS_LINKEDLIST_H
