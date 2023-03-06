// BubbleSort with doubly linked list

#include <iostream>
#include "list.cpp"

using namespace std;

int main(void){
    LinkedList *list = new LinkedList();
    // 70 1 12 8 99 72 5 15 20 91 14 61 66 41 81 88 16 21 34 90
    list->add(70);
    list->add(45);
    list->add(24);
    list->add(35);
    list->add(5);

    list->print();

    //list->bubbleSort();
    list->recursiveFasterBubbleSort(list->head, list->head->next, list->getSize());
}