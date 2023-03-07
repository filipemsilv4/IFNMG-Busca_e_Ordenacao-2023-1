// BubbleSort with doubly linked list

#include <iostream>
#include "list.cpp"
#include <chrono>

using namespace std;

int main(void){
    char seeList, seeTime;

    // Ask the user if he wants to see the list after each iteration
    do{
        cout << "Do you want to see the list after each iteration? (y/n) ";
        cin >> seeList;
        if (seeList != 'y' && seeList != 'n'){ cout << "Invalid answer. Please, try again." << endl; }
    } while (seeList != 'y' && seeList != 'n');

    // Ask the user if he wants to see the time of execution
    do{
        cout << "Do you want to see the time of execution? (y/n) ";
        cin >> seeTime;
        if (seeTime != 'y' && seeTime != 'n'){ cout << "Invalid answer. Please, try again." << endl; }
    } while (seeTime != 'y' && seeTime != 'n');

    LinkedList *list = new LinkedList();

    // Add 10 random numbers to the list
    for (int i = 0; i < 10; i++){ list->add(rand() % 1000); }
    
    // Print the list
    if (seeList == 'y'){ 
        cout << "Initial list: ";
        list->print();
    }

    if (seeTime == 'y'){
        auto start = chrono::high_resolution_clock::now();
        list->bubbleSort(list->head, list->head->next, list->getSize(), seeList);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
        return 0;
    }
    list->bubbleSort(list->head, list->head->next, list->getSize(), seeList);
    return 0;
}

