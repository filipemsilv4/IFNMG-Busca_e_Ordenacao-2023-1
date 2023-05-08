#include "sort.hpp"
#include <algorithm>
#include <iostream>

#include <stdio.h>
#include <math.h>

/*// Donut (I guess we will keep it commented since it is so cool)
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>*/

using namespace std;


// Função para fazer a troca de dois elementos em um vetor
void swap(vector<int>& v, int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


void print_vector(vector<int>& v){
    for (int i = 0; i < v.size(); i++) { cout << v[i] << " "; }
    cout << endl;
}


/*------------*/
// MERGE SORT //
/*------------*/

void merge_aux(vector<int>& v, int left, int mid, int right, bool show_list_state){
    // Create a temporary vector to store the sorted elements
    vector<int> tmp(right - left + 1);

    // Since we need to work with indices, we need to keep track of the indices of the left and right subarrays
    int l = left, m = mid;

    // Merge the two subarrays
    for(int i = 0; i < tmp.size(); i++){
        if(l > mid - 1){  // If the left subarray is empty, copy the rest of the right subarray
            tmp[i] = v[m++];
        }else if(m > right){  // If the right subarray is empty, copy the rest of the left subarray
            tmp[i] = v[l++];
        }else if(v[l] < v[m]){  // If the left element is smaller, copy it
            tmp[i] = v[l++];
        }else{  // If the right element is smaller, copy it
            tmp[i] = v[m++];
        }
    }

    // Copy the sorted elements back to the original vector
    for(int i = 0; i < tmp.size(); i++){
        v[left + i] = tmp[i];
    }

    if (show_list_state) {
        cout << "Current state: ";
        print_vector(v);
    }
}


void merge_sort(vector<int>& v, int left, int right, bool show_list_state){  
    if(left < right){  // Base case: 1 or 0 elements (already sorted)
        int mid = (left + right) / 2;
        merge_sort(v, left, mid, show_list_state);       // Sort left half
        merge_sort(v, mid + 1, right, show_list_state);  // Sort right half
        merge_aux(v, left, mid + 1, right, show_list_state); // Merge the two halves
    }
}


/*-----------*/
// HEAP SORT //
/*-----------*/

// Function that transforms the vector into a maximum heap
void heapify(vector<int>& v, int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // Left = 2*i + 1
    int right = 2 * i + 2; // Right = 2*i + 2

    // If left child is larger than root
    if (left < n && v[left] > v[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && v[right] > v[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(v, i, largest);

        // Recursively heapify the affected sub-tree
        heapify(v, n, largest);
    }
}


// Main function of Heapsort
void heap_sort(vector<int>& v, bool show_list_state) {
    int n = v.size();

    // Transforms the vector into a maximum heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(v, n, i);

    // Extracts the elements from the heap one by one
    for (int i = n - 1; i >= 0; i--) {
        // Shows the state of the list after each iteration
        if (show_list_state) {
            cout << "Current state: ";
            print_vector(v);
        }
        // Moves the root (largest element) to the end
        swap(v, 0, i);

        // Transforms the vector into a maximum heap again, excluding the last element
        heapify(v, i, 0);

    }
}


/*void heap_sort(vector<int>& v){
    // Originally Code by Andy Sloane https://www.a1k0n.net/2011/07/20/donut-math.html
    float A = 0, B = 0, i, j, z[1760];
    char b[1760];
    initscr(); // Initialize ncurses
    noecho(); // Don't echo keystrokes to the screen
    curs_set(0); // Hide the cursor
    clear(); // Clear the screen
    for(;;) {
        memset(b, 32, 1760);
        memset(z, 0, 7040);
        for(j = 0; 6.28 > j; j += 0.07) {
            for(i = 0; 6.28 > i; i += 0.02) {
                float c = sin(i), d = cos(j), e = sin(A), f = sin(j), g = cos(A), h = d + 2, D = 1 / (c * h * e + f * g + 5), l = cos(i), m = cos(B), n = sin(B), t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n), y = 12 + 15 * D * (l * h * n + t * m), o = x + 80 * y, N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if(22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }
        move(0, 0); // Move the cursor to the top-left corner of the screen
        for(int k = 0; 1761 > k; k++) {
            addch(k % 80 ? b[k] : '\n');
        }
        
        mvprintw(11, 20, "┌────────────────────────────────────────┐");
        mvprintw(12, 20, "│ Heap Sort Function Not Implemented Yet │"); // Print the message in the center of the screen
        mvprintw(13, 20, "└────────────────────────────────────────┘");
        refresh(); // Refresh the screen
        A += 0.04;
        B += 0.02;
        usleep(50000); // Sleep for 50 milliseconds to slow down the animation
    }
    endwin(); // End ncurses mode
}*/


/*-----------*/
//  WRAPPER  //
/*-----------*/

// Wrapper function for the sorting algorithms
void sort_wrapper(vector<int>& v, string algorithm, int left, int right, bool show_list_state, bool stress_mode){    
    if(algorithm == "Merge Sort"){
        merge_sort(v, left, right, show_list_state);
    }else if(algorithm == "Heap Sort"){
        heap_sort(v, show_list_state);
    }

    // Prints the sorted vector
    if (!stress_mode) {
        cout << "Sorted vector: ";
        print_vector(v);
    }
}
