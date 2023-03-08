#include <iostream>
#include <chrono>

using namespace std;

void stressMode(char);
void bubbleSort(int [], int);
void fasterBubbleSort(int [], int);
void displayArray(int [], int);
void generateRandomArray(int [], int);
void recursiveFasterBubbleSort(int [], int);


int main(int argc, char *argv[]){

    // Stress mode test
    if (argc == 3 && string(argv[2]) == "-stress"){
        if ((argv[1][0] != 'f' && argv[1][0] != 'r' && argv[1][0] != 'n')){
            cout << argv[1][0] << " is an not option" << endl;
            return 0;
        }
        stressMode(argv[1][0]);
        return 0;
    }
    

    // Ensure that the user has entered a VALID command line argument
    if (argc != 2 || (argv[1][0] != 'f' && argv[1][0] != 'r' && argv[1][0] != 'n')){
        cout << "Usage: sort f|n|r" << endl;
        cout << "f = faster bubble sort" << endl;
        cout << "n = normal bubble sort" << endl;
        cout << "r = recursive faster bubble sort" << endl;
        cout << "f|n|r -stress = sort with stress mode" << endl;

        return 1;
    }



    int values[] = { 5, 7, 2, 8, 9, 1, 4, 3, 6 };
    int size = sizeof(values) / sizeof(int);

    generateRandomArray(values, size);

    cout << "The unsorted values are " << endl;

    displayArray(values, size);

    if (argc > 1 && argv[1][0] == 'f'){
        for (int i = 0; i < 100000; i++){
            // Generate a random array each iteration
            generateRandomArray(values, size);
            fasterBubbleSort(values, size);
            cout << "The sorted values are " << endl;
            displayArray(values, size);
        }
    } else if (argc > 1 && argv[1][0] == 'r'){
        for (int i = 0; i < 100000; i++){
            // Generate a random array each iteration
            generateRandomArray(values, size);
            recursiveFasterBubbleSort(values, size);

            cout << "The sorted values are " << endl;
            displayArray(values, size);
        }
    } else if (argc > 1 && argv[1][0] == 'n'){
        for (int i = 0; i < 100000; i++){
            // Generate a random array each iteration
            generateRandomArray(values, size);
            bubbleSort(values, size);

            cout << "The sorted values are " << endl;
            displayArray(values, size);
        }
    }

    // print argc and argv[1][0]
    cout << "argc = " << argc << endl;
    cout << "argv[1][0] = " << argv[1][0] << endl;

    return 0;
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
void bubbleSort(int array[], int size){
    for (int i = 0; i < size - 1; i++)  // Last i elements are already in place
        for (int j = 0; j < size - 1; j++)  // Move the largest element to the end
            if (array[j] > array[j + 1]){
                swap(array[j], array[j + 1]);
                /* cout << "The array is now ";
                displayArray(array, size); */
            }
}


// Faster Bubble Sort
void fasterBubbleSort(int array[], int size){
    // we will skip the already sorted elements, reducing the size of the array
    int newSize = size;

    for (int i = 0; i < size - 1; i++){
        // if no swap is made, the array is sorted
        bool swapped = false;

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
void recursiveFasterBubbleSort(int array[], int size){
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
    if (!swapped)
        return;

    // the last element is sorted, so we can skip it
    newSize--;

    // sort the remaining array
    recursiveFasterBubbleSort(array, newSize);
}

void stressMode(char option){
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
            fasterBubbleSort(values, howManyNumbers);
            break;
        case 'r':
            recursiveFasterBubbleSort(values, howManyNumbers);
            break;
        case 'n':
            bubbleSort(values, howManyNumbers);
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