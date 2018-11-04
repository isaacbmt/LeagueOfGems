//AGREGADO POR GABRIEL

#ifndef LEAGUEOFGEMS_LINKEDLISTGEN_H
#define LEAGUEOFGEMS_LINKEDLISTGEN_H

#include <iostream>
#include "Node.h"

template <typename T>

class LinkedListGen{

private:
    int size;
    Node<T> *head;

public:

    LinkedListGen() {
        head = nullptr;
        size = 0;
    }

    void add(T data) {
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

    void remove(int index){
        if (index == 0){
            Node<T> *tmp;
            tmp = head;
            head = head->getNext();
            size--;
            free (tmp);
            return;
        }
        else{
            Node<T> *tmp = head;
            Node<T> *tmp2;

            for (int i = 0; i < size; ++i) {
                if (i == index){
                    tmp2->setNext(tmp->getNext());
                    free (tmp);
                    size--;
                    return;
                }
                tmp2 = tmp;
                tmp = tmp->getNext();
            }
        }
    }

    T get(int index){
        Node<T> *tmp = head;
        for (int i = 0; i < index; ++i) {
            tmp = tmp->getNext();
        }
        return tmp->getData();
    }

    void set_Data(int index,T data){
        Node<T> *tmp = head;
        for (int i = 0; i < index; ++i) {
            tmp = tmp->getNext();
        }
        return tmp->setData(data);
    }


    int length(){
        return size;
    }

};


#endif //LEAGUEOFGEMS_LINKEDLISTGEN_H
