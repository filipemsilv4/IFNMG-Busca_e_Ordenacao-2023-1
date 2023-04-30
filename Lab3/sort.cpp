#include <vector>
#include <algorithm>
#include <iostream>

#include <stdio.h>
#include <string.h>
#include <math.h>

// Donut (remember to delete this)
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>


using namespace std;


void merge_aux(vector<int>& v, int left, int mid, int right){
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
}


void merge_sort(vector<int>& v, int left, int right){  
    if(left < right - 1){  // Base case: 1 or 0 elements (already sorted)
        int mid = (left + right) / 2;
        merge_sort(v, left, mid);       // Sort left half
        merge_sort(v, mid, right);  // Sort right half
        merge_aux(v, left, mid, right); // Merge the two halves
    }
}

// heap_sort
int parent(int i){ return (i/2); }
int left(int i){ return (2*i); }
int right(int i){ return (2*i + 1); }

void heapify(vector<int>& v, int i){
    int l = left(i);
    int r = right(i);
    int g;

    if ((l < v.size()) && v[l] > v[i]){ g = l; }
    else{ g = i; }

    if ((r <= v.size()) && v[r] > v[g]){ g = r; }

    if(g != i){
        swap(v[i], v[g]);
        heapify(v, g);
    }
}

void create_heap(vector<int>& v){
    int m = (v.size() - 1)/2;
    for (int i = m; i > 0; i--){ heapify(v, i); }
}

void heap_sort(vector<int>& v, bool show_list_state){
    create_heap(v);
    int f = v.size() - 1;
    for (int i = f; i >= 0; i--)
    {
        swap(v[1], v[i]);
        heapify(v, 1);
        if (show_list_state) {
            cout << "Current state: ";
            for (int i = 0; i < v.size(); i++) {
                cout << v[i] << " ";
            }
            cout << endl;
        }
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


void sort_wrapper(vector<int>& v, string algorithm, int left, int right, bool show_list_state){    
    if(algorithm == "Merge Sort"){
        merge_sort(v, left, right);
    }else if(algorithm == "Heap Sort"){
        heap_sort(v);
    }
}
