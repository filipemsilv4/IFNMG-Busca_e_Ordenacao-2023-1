#include <iostream>
#include <chrono>
#include "sort.cpp"
#include <ncurses.h>
#include <vector>
#include <utility>
#include <locale.h>

using namespace std;

void stressMode();

int main() {
    setlocale(LC_ALL, "");

    // Initialize ncurses
    if (initscr() == nullptr) {
        fprintf(stderr, "Error initializing ncurses.\n");
        return 1;
    }
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Define options
    vector<pair<string, bool>> options = {
        {"Mostrar o estado da lista a cada iteração", false},
        {"Mostrar o tempo de execução do algoritmo ", false},
        {"OK", false}
    };

    // Set initial selected option
    int selected_option = 0;

    // Loop until user selects an option or exits
    bool done = false;
    while (!done) {
        // Clear screen
        clear();

        // Print options
        printw(" ┌────────────────────────────────────────────────┐\n");
        printw(" │ Selecione as opções desejadas:                 │\n");
        printw(" │                                                │\n");
        for (int i = 0; i < options.size() - 1; i++) {
            if (i == selected_option) {
                attron(A_REVERSE); // Highlight selected option
            }
            printw(" │  %-41s [%s] │\n", options[i].first.c_str(), options[i].second ? "X" : " ");
            attroff(A_REVERSE); // Disable highlighting
        }
        if (selected_option == options.size() - 1) {
            attron(A_REVERSE); // Highlight selected option
        }
        printw(" │  %-45s │\n", options[options.size() - 1].first.c_str());
        attroff(A_REVERSE); // Disable highlighting
        printw(" │                                                │\n");
        printw(" │ Use as setas para selecionar e ENTER para      │\n");
        printw(" │ confirmar.                                     │\n");
        printw(" └────────────────────────────────────────────────┘\n");

        // Get user input
        int key = getch();

        // Move selection based on user input
        switch (key) {
            case KEY_UP:
                selected_option = (selected_option - 1 + options.size()) % options.size();
                break;
            case KEY_DOWN:
                selected_option = (selected_option + 1) % options.size();
                break;
            case '\n': // User pressed enter
                if (selected_option == options.size() - 1) {
                    done = true; // Exit loop
                } else {
                    options[selected_option].second = !options[selected_option].second; // Toggle option
                }
                break;
            default:
                break;
        }
    }

    // Terminate ncurses
    endwin();
    return 0;
}



/* int main() {
    int stress = 1;
    //cin >> stress;
    if (stress == 1){
        stressMode();
        return 0;
    }

    vector<int> nums = { 70, 1, 12, 8, 99, 72, 5, 15, 20, 91, 14, 61, 66, 41, 81, 88, 16, 21, 34, 90 };
    
    quicksort(nums, 0, nums.size() - 1);
    
    for (int num : nums) {
        cout << num << " ";
    }
    
    return 0;
} */

void stressMode(){
    // Generate 1000 random lists, each with a random number of random elements
    // Print the average time it took to sort all the lists

    cout << "Number of elements,Time taken by the sorting function" << endl;
    
    auto startAll = chrono::high_resolution_clock::now();
    auto averageTime = 0;

    // Generate 1000 random lists
    for (int i = 0; i < 1000; i++){
        // Generate a list with i elements
        vector<int> *list = new vector<int>();
        for (int j = 0; j < i; j++){
            list->push_back(rand() % 1000);  // Random number between 0 and 999
        }
        
        // Sort the list
        auto start = chrono::high_resolution_clock::now();
        quicksort(*list, 0, list->size() - 1);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        
        averageTime += duration.count();

        // Print the number of elements of the list and the time it took to sort it
        cout << i << "," << duration.count() << endl;
        
        // Delete the list
        delete list;
    }
    auto endAll = chrono::high_resolution_clock::now();

    // Average time: 0.0000000
    cout << endl << "Average time: " << averageTime / 1000 << " microseconds" << endl;

    // Total time: 0.0000000
    auto durationAll = chrono::duration_cast<chrono::microseconds>(endAll - startAll);
    cout << "Total time  : " << durationAll.count() << " microseconds" << endl << endl;
}
