// BubbleSort with doubly linked list

#include <iostream>
#include "list.cpp"
#include <chrono>

using namespace std;

int main(int argc, char *argv[]){
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

    // Ask the user if he wants to manually add numbers to the list
    char manuallyAdd;
    do{
        cout << "Do you want to manually add numbers to the list? (y/n) ";
        cin >> manuallyAdd;
        if (manuallyAdd != 'y' && manuallyAdd != 'n'){ cout << "Invalid answer. Please, try again." << endl; }
    } while (manuallyAdd != 'y' && manuallyAdd != 'n');

    if (manuallyAdd == 'y'){
        string input;
        int number;
        while (true){
            cout << "Enter a value to add to the list (type 'end' to stop): ";
            cin >> input;
            
            if (input == "end"){ break; }
            
            try{
                number = stoi(input);
                list->add(number);
            } catch (exception e){
                cout << "Invalid input. Please, try again." << endl;
            }
        }
        if (list->getSize() == 0){
            cout << "How do you expect me to sort a list of size zero?" << endl;
            return 0;
        }
    } else {
        int howManyNumbers;
        while (true){
            cout << "How many numbers do you want to be randomly generated and added to the list? ";
            cin >> howManyNumbers;
            if (!cin.fail() && howManyNumbers >= 1){ break; }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please, try again." << endl;
        }

        for (int i = 0; i < howManyNumbers; i++){ list->add(rand() % 1000); }
    }
    
    // Print the list
    if (seeList == 'y'){ 
        cout << endl << "Initial list: ";
        list->print();
        cout << endl;
    }

    if (seeTime == 'y'){
        auto start = chrono::high_resolution_clock::now();
        list->bubbleSort(list->head, list->head->next, list->getSize(), seeList);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << endl << "Time taken by the sorting function: " << duration.count() << " microseconds" << endl;
        return 0;
    }
    list->bubbleSort(list->head, list->head->next, list->getSize(), seeList);
    return 0;
}

