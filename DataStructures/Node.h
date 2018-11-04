//AGREGADO POR GABRIEL

#ifndef LEAGUEOFGEMS_NODE_H
#define LEAGUEOFGEMS_NODE_H

#include <iostream>

template <typename T>

class Node {

private:
    Node<T> *next;
    T data;

public:
    Node(T data){
        this->data = data;
        next = nullptr;
    }

    void setNext(Node<T> *next){
        this->next = next;
    }

    Node<T>* getNext(){
        return next;
    }

    T getData(){
        return data;
    }

    void setData(T data){
        this->data=data;
    }

    ~Node(){
        next = nullptr;
        data = nullptr;
    }

};


#endif //LEAGUEOFGEMS_NODE_H
