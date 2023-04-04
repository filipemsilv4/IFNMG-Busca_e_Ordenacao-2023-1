// Compile with "g++ -o main main.cpp -lncurses"
#include <iostream>
#include <chrono>
#include <ncurses.h>
#include <vector>
#include <utility>
#include <locale.h>
#include "sort.cpp"

using namespace std;

void waitForWindowWidth(int min_width);
void display_options(vector<pair<string, bool>>& options, int max_option_length);
void stressMode(bool show_state);


int main(int argc, char** argv) {
    // if -TUI_stresses_me is passed as an argument, ignore TUI and run stress mode
    if (argc >= 2 && std::string(argv[1]) == "-TUI_stresses_me") {
        stressMode(false);
        return 0;
    }
    
    setlocale(LC_ALL, "");

    // Initialize ncurses
    if (initscr() == nullptr) {
        fprintf(stderr, "Error initializing ncurses.\n");
        return 1;
    }
    cbreak(); // Disable line buffering (so we can get user input immediately)
    noecho(); // Disable echoing of user input
    curs_set(0); // Hide cursor
    keypad(stdscr, TRUE); // Enable special keys (like arrow keys)


    // Define options
    vector<pair<string, bool>> options = {
        {"Show the state of the list at each iteration", false},
        {"Show the execution time of the algorithm", false},
        //{"Run with 1000 random lists of increasing size", false},
        {"OK", false},
        {"Ignore and run StressMode", false}
    };

    // Define display_options function's header and bottom texts
    string title = "Select StressMode or the desired options for standart mode:";
    string instructions = "Use the arrows to select, then confirm with ENTER";

    // Calculate the length of the longest string (including title and instructions)
    int max_option_length = title.length();
    for (int i = 0; i < options.size(); i++) {
        if (options[i].first.length() > max_option_length) {
            max_option_length = options[i].first.length();
        }
    }
    if (instructions.length() > max_option_length) {
        max_option_length = instructions.length();
    }

    // Display options and store the ones selected by the user
    display_options(options, max_option_length);

    curs_set(1);
    // Stress mode
    if (options[3].second) {
        endwin();
        stressMode(options[3].second);
        return 0;
    }else{}



    // Terminate ncurses
    endwin();

    // Print selected options
    cout <<"\n\n_______________________________\n";
    for (int i = 0; i < options.size() - 1; i++) {
        cout << options[i].first << ": " << (options[i].second ? "Yes" : "No") << endl;
    }
    
    return 0;
}


void waitForWindowWidth(int min_width) {
    clear();  // clear the screen
    int cols;
    int tmp;

    curs_set(0);  // hide cursor
    cols = getmaxx(stdscr);  // get window width
    tmp = cols;

    while (cols < min_width) {
        mvprintw(0, 0, "  << The current terminal width is %d, please increase the size to at least %d. >>  ", cols, min_width);
        refresh();  // update the screen
        cols = getmaxx(stdscr);  // get updated window width
        if (tmp != cols) {
            clear();  // clear the screen
            tmp = cols;
        }
    }

    curs_set(1);  // show cursor
}


void display_options(vector<pair<string, bool>>& options, int max_option_length){
    int selected_option = 0; // Used to keep track of the currently selected option (the one that is highlighted)
    int key; // Used to store the user input
    bool done = false; // Used to exit the loop

    string title = "Select StressMode or the desired options for standart mode:";
    string instructions = "Use the arrows to select, then confirm with ENTER";

    // Calculate the width of the box
    int box_width = max_option_length + 8;

    while (!done) {
        waitForWindowWidth(box_width + 1);
        curs_set(0);
        // Clear screen
        clear();

        // Print options
        // Header
        printw("┌");
        for (int i = 0; i < box_width - 2; i++) { printw("─"); }
        printw("┐\n");
        printw("│ %-*s │\n", box_width - 4, title.c_str());

        printw("├");
        for (int i = 0; i < box_width - 2; i++) { printw("─"); }
        printw("┤\n");

        // Options
        for (int i = 0; i < options.size() - 2; i++) {
            if (i == selected_option) {
                attron(A_REVERSE); // Highlight selected option
            }
            printw("│ %-*s[%s] │\n", max_option_length + 1, options[i].first.c_str(), options[i].second ? "X" : " ");
            attroff(A_REVERSE); // Disable highlighting
        }

        // Decoration for last buttons
        printw("│ ┌");
        for (int i = 0; i < max_option_length / 2 - 1; i++) { printw("─"); }
        printw("┐ ");

        printw(" ┌");
        for (int i = 0; i < max_option_length / 2; i++) { printw("─"); }
        printw("┐ │\n");

        // Penultimate option
        printw("│ │");
        if (selected_option == options.size() - 2) {
            attron(A_REVERSE); // Highlight selected option
        }
        printw(" %-*s", max_option_length / 2 - 2, options[options.size() - 2].first.c_str());
        attroff(A_REVERSE); // Disable highlighting
        printw("│ ");

        // Last option
        printw(" │");
        if (selected_option == options.size() - 1) {
            attron(A_REVERSE); // Highlight selected option
        }
        printw(" %-*s", max_option_length / 2 - 1, options[options.size() - 1].first.c_str());
        attroff(A_REVERSE); // Disable highlighting
        printw("│ │\n");

        printw("│ └");
        for (int i = 0; i < max_option_length / 2 - 1; i++) { printw("─"); }
        printw("┘ ");

        printw(" └");
        for (int i = 0; i < max_option_length / 2; i++) { printw("─"); }
        printw("┘ │\n");

        printw("├");
        for (int i = 0; i < box_width - 2; i++) { printw("─"); }
        printw("┤\n");

        // Instructions
        printw("│ %-*s │\n", box_width - 4, instructions.c_str());
        printw("└");
        for (int i = 0; i < box_width - 2; i++) { printw("─"); }
        printw("┘\n");

        // Get user input
        key = getch();

        // Move selection based on user input
        switch (key) {
            case KEY_UP:
                // if we are in the last option, we dont want to go to the penultimate option, so we go up 2 options
                if (selected_option == options.size() - 1) {
                    selected_option = (selected_option - 2 + options.size()) % options.size();
                } else {
                    selected_option = (selected_option - 1 + options.size()) % options.size();
                }
                break;
            case KEY_DOWN:
                selected_option = (selected_option + 1) % options.size();
                break;
            case KEY_LEFT:
                // If we are on the last option, go to the penultimate option, if we are in the penultimate option, go to the last option
                if (selected_option == options.size() - 1) {
                    selected_option = options.size() - 2;
                } else if (selected_option == options.size() - 2) {
                    selected_option = options.size() - 1;
                }
                break;
            case KEY_RIGHT:
                // If we are on the last option, go to the penultimate option, if we are in the penultimate option, go to the last option
                if (selected_option == options.size() - 1) {
                    selected_option = options.size() - 2;
                } else if (selected_option == options.size() - 2) {
                    selected_option = options.size() - 1;
                }
                break;
            case '\n': // User pressed enter
                if (selected_option == options.size() - 1) {
                    cout << "\n\n1. > " << options[selected_option].first;
                    done = true; // Exit loop
                } else if (selected_option == options.size() - 2){
                    cout << "\n\n" << selected_option << "\n\n2. > " << options[selected_option].first;
                    options[selected_option].second = true;
                } 
                else {
                    cout << selected_option << "\n\n3. > " << options[selected_option].first;
                    options[selected_option].second = true; // Toggle option
                }
                break;
            default:
                break;
        }
    }
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

void stressMode(bool show_state){
    // Generate 1000 random lists, each with a random number of random elements
    // Print the average time it took to sort all the lists

    cout << "Number of elements,Time taken by the sorting function" << endl;
    
    auto startAll = chrono::high_resolution_clock::now();
    auto averageTime = 0;

    // Generate 1000 random lists
    for (int i = 1; i <= 1000; i++){
        // Generate a list with i elements
        vector<int> *list = new vector<int>();
        for (int j = 0; j < i; j++){
            list->push_back(rand() % 1000);  // Random number between 0 and 999
        }
        
        // Sort the list
        auto start = chrono::high_resolution_clock::now();
        quicksort(*list, 0, list->size() - 1, show_state);
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
