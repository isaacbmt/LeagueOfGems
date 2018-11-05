//
// Created by leahycarlos21 on 4/11/18.
//

#ifndef LEAGUEOFGEMS_HEAP_H
#define LEAGUEOFGEMS_HEAP_H

template<typename T>
struct nodeHeap {
    T data;
    nodeHeap *prev;
};


template<typename T>
class Heap {

public:
    nodeHeap<T> *head;
    int lenght = 0;

public:
    void push(T dato);
    T pop();
    T peek();
    int getLenght() { return this->lenght; };

};

template<typename T>
void Heap<T>::push(T dato) {
    if (head == nullptr) {
        head = new nodeHeap<T>();
        head->data = dato;
        head->prev = nullptr;
    } else {
        auto *nodeN = new nodeHeap<T>();
        nodeN->data = dato;
        nodeN->prev = head;
        head = nodeN;
    }
    this->lenght++;
}

template<typename T>
T Heap<T>::peek() {
    return this->head->data;
}

template<typename T>
T Heap<T>::pop() {
    nodeHeap<T> *aux;
    aux = head;
    head = head->prev;
    this->lenght--;
    return aux->data;
}

#endif //LEAGUEOFGEMS_HEAP_H
