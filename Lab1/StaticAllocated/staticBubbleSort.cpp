#include <iostream>
#include <chrono>
#include <cstdlib>

using namespace std;

void stressMode(char, char);
void bubbleSort(int [], int, char);
void fasterBubbleSort(int [], int, char);
void displayArray(int [], int);
void generateRandomArray(int [], int);
void recursiveFasterBubbleSort(int [], int, char);
void usage();

int ogListSize = 0;

int main(int argc, char *argv[]){
    // Ensure that the user has entered a VALID command line argument
    if (argc < 2 || (argv[1][0] != 'f' && argv[1][0] != 'r' && argv[1][0] != 'n')){
        usage();
        return 0;
    }

    // Ask if the user wants to see the list after each iteration
    cout << "Do you want to see the list after each iteration? (y/n) ";
    char seeList; cin >> seeList;

    // Stress mode test
    if (argc == 3 && string(argv[2]) == "-stress"){
        stressMode(argv[1][0], seeList);
        return 0;
    }

    int values[] = { 70, 1, 12, 8, 99, 72, 5, 15, 20, 91, 14, 61, 66, 41, 81, 88, 16, 21, 34, 90 };
    int size = sizeof(values) / sizeof(int);
    ogListSize = size;

    if      (argc > 1 && argv[1][0] == 'f'){ fasterBubbleSort(values, size, seeList); }
    else if (argc > 1 && argv[1][0] == 'r'){ recursiveFasterBubbleSort(values, size, seeList); }
    else if (argc > 1 && argv[1][0] == 'n'){ bubbleSort(values, size, seeList); }

    cout << "The sorted values are " << endl;
    displayArray(values, size);

    return 0;
}

// Ensure proper use of the program
void usage(){
    cout << "Usage: sort f|n|r" << endl;
    cout << "f = faster bubble sort" << endl;
    cout << "n = normal bubble sort" << endl;
    cout << "r = recursive faster bubble sort" << endl;
    cout << "f|n|r -stress = sort with stress mode" << endl;
}


// Generate a random array
void generateRandomArray(int array[], int size){
    for (int count = 0; count < size; count++)
        array[count] = rand() % 100;
}


// Display the array
void displayArray(int array[], int size){
    for (int count = 0; count < size; count++)
        cout << array[count] << " ";
    cout << endl;
}


// Bubble sort
void bubbleSort(int array[], int size, char seeList){
    for (int i = 0; i < size - 1; i++){  // Last i elements are already in place
        if (seeList == 'y'){ displayArray(array, size); }
        for (int j = 0; j < size - 1; j++){  // Move the largest element to the end
            if (array[j] > array[j + 1]){ swap(array[j], array[j + 1]); }
        }
    }
}


// Faster Bubble Sort
void fasterBubbleSort(int array[], int size, char seeList){
    // we will skip the already sorted elements, reducing the size of the array
    int newSize = size;

    for (int i = 0; i < size - 1; i++){
        // if no swap is made, the array is sorted
        bool swapped = false;

        if (seeList == 'y'){ displayArray(array, size); }

        for (int j = 0; j < newSize - 1; j++)
            if (array[j] > array[j + 1]){
                swap(array[j], array[j + 1]);
                swapped = true;
            }

        // if no swap is made, the array is sorted
        if (!swapped)
            break;

        // the last element is sorted, so we can skip it
        newSize--;
    }
}


// Recursive Faster Bubble Sort
void recursiveFasterBubbleSort(int array[], int size, char seeList){
    // if the array is empty or has only one element, it is sorted
    if (size == 1){ return; }

    // we will skip the already sorted elements, reducing the size of the array
    int newSize = size;

    // if no swap is made, the array is sorted
    bool swapped = false;

    for (int j = 0; j < newSize - 1; j++){
        if (array[j] > array[j + 1]){
            swap(array[j], array[j + 1]);
            swapped = true;
        }
    }

    // if no swap is made, the array is sorted
    if (!swapped){ return; }
    
    if (seeList == 'y'){ displayArray(array, ogListSize); }

    // the last element is sorted, so we can skip it
    newSize--;

    // sort the remaining array
    recursiveFasterBubbleSort(array, newSize, seeList);
}

void stressMode(char option, char seeList){
    // Generate 1000 random vectors, each with a random number of random elements
    // Print the average time it took to sort all the vectors

    auto startAll = chrono::high_resolution_clock::now();
    auto averageTime = 0;

    cout << "Number of elements,Time taken by the sorting function" << endl;

    // Generate 1000 random lists
    for (int i = 0; i < 1000; i++){
        int howManyNumbers = rand() % 1000 + 1;
        int values[howManyNumbers];
        generateRandomArray(values, howManyNumbers);

        // Generate a random number of elements

        // Sort the vector
        auto start = chrono::high_resolution_clock::now();
        switch (option)
        {
        case 'f':
            fasterBubbleSort(values, howManyNumbers, seeList);
            break;
        case 'r':
            recursiveFasterBubbleSort(values, howManyNumbers, seeList);
            break;
        case 'n':
            bubbleSort(values, howManyNumbers, seeList);
            break;
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        
        averageTime += duration.count();

        // Print the number of elements of the vector and the time it took to sort it
        cout << howManyNumbers << "," << duration.count() << endl;

    }
    auto endAll = chrono::high_resolution_clock::now();

    // Average time: 0.0000000
    cout << endl << "Average time: " << averageTime / 1000 << " microseconds" << endl;

    // Total time: 0.0000000
    auto durationAll = chrono::duration_cast<chrono::microseconds>(endAll - startAll);
    cout << "Total time  : " << durationAll.count() << " microseconds" << endl << endl;
}


// I hope it works