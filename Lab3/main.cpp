// Compile with "g++ -o main main.cpp -lncurses -std=c++11"
#include <locale.h>
#include <ncurses.h>

#include <chrono>
#include <iostream>
#include <utility>
#include <vector>
#include <map>

#include "sort.cpp"

using namespace std;

map<string, int> waitForWindowWidth(int min_width);
void display_options(vector<pair<string, bool>> &options, int max_option_length, string title, string instructions);
void stressMode(bool show_state, string algorithm);

int main(int argc, char **argv) {
    // if -TUI_stresses_me is passed as an argument, ignore TUI and run stress mode
    if (argc >= 3 && string(argv[1]) == "-TUI_stresses_me") {
        if (string(argv[2]) == "merge_sort"){
            stressMode(false, "merge_sort");
        } else if (string(argv[2]) == "heap_sort"){
            stressMode(false, "heap_sort");
        } else {
            cout << "Invalid algorithm name" << endl;
        }
        return 0;
    }

    setlocale(LC_ALL, "");

    /*--------------------*/
    // Initialize ncurses //
    /*--------------------*/
    if (initscr() == nullptr) {
        fprintf(stderr, "Error initializing ncurses.\n");
        return 1;
    }
    cbreak();  // Disable line buffering (so we can get user input immediately)
    noecho();  // Disable echoing of user input
    curs_set(0);           // Hide cursor
    keypad(stdscr, TRUE);  // Enable special keys (like arrow keys)

    /*--------------------------------------------*/
    // Select wich sorting algorithm will be used //
    /*--------------------------------------------*/
    vector<pair<string, bool>> algorithm = {
        {"Merge Sort", false},
        {"Heap Sort", false},
    };

    // Define display_options function's header and bottom texts
    string title = "Select the desired sorting algorithm";
    string instructions = "Use the arrows to select, then confirm with ENTER";

    // Calculate the length of the longest string (including title and instructions)
    int max_option_length = title.length();
    for (int i = 0; i < algorithm.size(); i++) {
        if (algorithm[i].first.length() > max_option_length) {
            max_option_length = algorithm[i].first.length();
        }
    }
    if (instructions.length() > max_option_length) {
        max_option_length = instructions.length();
    }

    // Display options and store the ones selected by the user
    display_options(algorithm, max_option_length, title, instructions);

    string chosen_algorithm;
    if      (algorithm[0].second){ chosen_algorithm = algorithm[0].first; }
    else if (algorithm[1].second){ chosen_algorithm = algorithm[1].first; }
    else { return 0; }

    /*----------------------------------------------*/
    // Select the options to run the algorithm with //
    /*----------------------------------------------*/
    vector<pair<string, bool>> options = {
        {"Show the state of the list at each iteration", false},
        {"Show the execution time of the algorithm", false},
        {"OK", false},
        {"Ignore and run StressMode", false}};

    // Define display_options function's header text
    title = "Select StressMode or the desired options for standart mode:";

    // Calculate the length of the longest string (including title and instructions)
    max_option_length = title.length();
    for (int i = 0; i < options.size(); i++) {
        if (options[i].first.length() > max_option_length) {
            max_option_length = options[i].first.length();
        }
    }
    if (instructions.length() > max_option_length) {
        max_option_length = instructions.length();
    }

    // Display options and store the ones selected by the user
    display_options(options, max_option_length, title, instructions);

    curs_set(1);


    // Stress mode
    endwin();
    if (options[3].second) {
        stressMode(options[0].second, chosen_algorithm);
        return 0;
    } else if (options[2].second) {
        int size;
        cout << "\nType size of list: ";
        cin >> size;  // size list
        cout << "\n";
        vector<int> *list = new vector<int>();
        int number;

        for (int j = 0; j < size; j++) {
            cout << "Type the " << j + 1 << " number of list: ";
            cin >> number;
            list->push_back(number);
        }

        cout << "\n" << endl;

        // Show execution time
        if (options[1].second) {
            auto startAll = chrono::high_resolution_clock::now();
            auto averageTime = 0;

            // Sort the list
            auto start = chrono::high_resolution_clock::now();
            sort_wrapper(*list, chosen_algorithm, 0, list->size() - 1, options[0].second);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

            averageTime += duration.count();

            // Delete the list
            delete list;
            auto endAll = chrono::high_resolution_clock::now();

            // Average time: 0.0000000
            cout << endl
                 << "Average time: " << averageTime / 1000 << " microseconds"
                 << endl;

            // Total time: 0.0000000
            auto durationAll =
                chrono::duration_cast<chrono::microseconds>(endAll - startAll);
            cout << "Total time  : " << durationAll.count() << " microseconds"
                 << endl
                 << endl;
        } else {
            sort_wrapper(*list, chosen_algorithm, 0, list->size() - 1, options[0].second);
        }

        for (int i = 0; i < list->size(); i++) {
            cout << list->at(i) << " ";
        }
        cout << endl;
    }

    return 0;
}


map<string, int> waitForWindowWidth(int min_width) {
    clear();  // clear the screen
    int cols;
    int lines;
    int tmp;

    curs_set(0);             // hide cursor
    cols = getmaxx(stdscr);  // get window width
    tmp = cols;
    lines = getmaxy(stdscr);  // get window height

    map<string, int> win_size = {
        {"height", lines},
        {"width", cols}
    };

    while (cols < min_width) {
        mvprintw(0, 0,
                 "  << The current terminal width is %d, please increase the "
                 "size to at least %d. >>  ",
                 cols, min_width);
        refresh();               // update the screen
        cols = getmaxx(stdscr);  // get updated window width
        if (tmp != cols) {
            clear();  // clear the screen
            tmp = cols;
        }
    }

    curs_set(1);  // show cursor

    return win_size;
}


void display_options(vector<pair<string, bool>> &options, int max_option_length, string title, string instructions) {
    int highlighted_option = 0;  // Used to keep track of the currently selected
                              // option (the one that is highlighted)
    int key;                  // Used to store the user input
    bool done = false;        // Used to exit the loop

    // Calculate the width of the box
    int box_width = max_option_length + 8;
    // Calculate the height of the box
    int box_height = options.size() + 6;

    while (!done) {
        auto win_size = waitForWindowWidth(box_width + 1);
        curs_set(0);
        // Clear screen
        clear();

        // Centre the box
        int top_margin = (win_size["height"] / 2) - (box_height / 2) - 1;
        int left_margin = (win_size["width"] / 2) - (box_width / 2) - 1;
        move(top_margin, left_margin);

        // Print options
        // Header
        printw("┌");
        for (int i = 0; i < box_width - 2; i++) {
            printw("─");
        }
        printw("┐\n");
        move(++top_margin, left_margin);
        printw("│ %-*s │\n", box_width - 4, title.c_str());
        move(++top_margin, left_margin);

        printw("├");
        for (int i = 0; i < box_width - 2; i++) {
            printw("─");
        }
        printw("┤\n");
        move(++top_margin, left_margin);

        // Options
        for (int i = 0; i < options.size() - 2; i++) {
            if (i == highlighted_option) {
                attron(A_REVERSE);  // Highlight selected option
            }
            printw("│ %-*s[%s] │\n", max_option_length + 1, options[i].first.c_str(), options[i].second ? "X" : " ");
            move(++top_margin, left_margin);
            attroff(A_REVERSE);  // Disable highlighting
        }

        // Decoration for last buttons
        printw("│ ┌");
        for (int i = 0; i < max_option_length / 2 - 1; i++) {
            printw("─");
        }
        printw("┐ ");

        printw(" ┌");
        for (int i = 0; i < max_option_length / 2; i++) {
            printw("─");
        }
        printw("┐ │\n");
        move(++top_margin, left_margin);

        // Penultimate option
        printw("│ │");
        if (highlighted_option == options.size() - 2) {
            attron(A_REVERSE);  // Highlight selected option
        }
        printw(" %-*s", max_option_length / 2 - 2,
               options[options.size() - 2].first.c_str());
        attroff(A_REVERSE);  // Disable highlighting
        printw("│ ");

        // Last option
        printw(" │");
        if (highlighted_option == options.size() - 1) {
            attron(A_REVERSE);  // Highlight selected option
        }
        printw(" %-*s", max_option_length / 2 - 1,
               options[options.size() - 1].first.c_str());
        attroff(A_REVERSE);  // Disable highlighting
        printw("│ │\n");
        move(++top_margin, left_margin);

        printw("│ └");
        for (int i = 0; i < max_option_length / 2 - 1; i++) {
            printw("─");
        }
        printw("┘ ");

        printw(" └");
        for (int i = 0; i < max_option_length / 2; i++) {
            printw("─");
        }
        printw("┘ │\n");
        move(++top_margin, left_margin);

        printw("├");
        for (int i = 0; i < box_width - 2; i++) {
            printw("─");
        }
        printw("┤\n");
        move(++top_margin, left_margin);

        // Instructions
        printw("│ %-*s │\n", box_width - 4, instructions.c_str());
        move(++top_margin, left_margin);
        printw("└");
        for (int i = 0; i < box_width - 2; i++) {
            printw("─");
        }
        printw("┘\n");
        move(++top_margin, left_margin);

        // Get user input
        key = getch();

        // Move selection based on user input
        switch (key) {
            case KEY_UP:
                // if we are in the last option, we dont want to go to the
                // penultimate option, so we go up 2 options
                if (highlighted_option == options.size() - 1 && options.size() > 2) {
                    highlighted_option = (highlighted_option - 2 + options.size()) % options.size();
                } else {
                    highlighted_option = (highlighted_option - 1 + options.size()) % options.size();
                }
                break;
            case KEY_DOWN:
                highlighted_option = (highlighted_option + 1) % options.size();
                break;
            case KEY_LEFT:
                // If we are on the last option, go to the penultimate option,
                // if we are in the penultimate option, go to the last option
                if (highlighted_option == options.size() - 1) {
                    highlighted_option = options.size() - 2;
                } else if (highlighted_option == options.size() - 2) {
                    highlighted_option = options.size() - 1;
                }
                break;
            case KEY_RIGHT:
                // If we are on the last option, go to the penultimate option,
                // if we are in the penultimate option, go to the last option
                if (highlighted_option == options.size() - 1) {
                    highlighted_option = options.size() - 2;
                } else if (highlighted_option == options.size() - 2) {
                    highlighted_option = options.size() - 1;
                }
                break;
            case '\n':  // User pressed enter
                // If there's only 2 options, they are the 2 buttons on the bottom
                if (options.size() < 2){
                    if (highlighted_option == 0){
                        options[highlighted_option].second = !options[highlighted_option].second;
                        done = true;  // Exit loop
                    } else if (highlighted_option == 1){
                        options[highlighted_option].second = !options[highlighted_option].second;
                        done = true;  // Exit loop
                    }
                } else {
                    // Iterate trough the options and update their value
                    for (int i = 0; i < options.size() - 2; i++){
                        if (highlighted_option == i){
                            options[highlighted_option].second = !options[highlighted_option].second;
                        }
                    }
                    // If the user selects one of the last 2 options, set done to true
                    if (highlighted_option == options.size() - 1){
                        options[highlighted_option].second = !options[highlighted_option].second;
                        done = true;
                    } else if (highlighted_option == options.size() - 2){
                        options[highlighted_option].second = !options[highlighted_option].second;
                        done = true;
                    }
                }
                break;
            default:
                break;
        }
    }
}


void stressMode(bool show_state, string algorithm) {
    // Generate 1000 random lists, each with a random number of random elements
    // Print the average time it took to sort all the lists

    cout << "Number of elements,Time taken by the sorting function" << endl;

    auto startAll = chrono::high_resolution_clock::now();
    auto averageTime = 0;

    // Generate 1000 random lists
    for (int i = 1; i <= 1000; i++) {
        // Generate a list with i elements
        vector<int> *list = new vector<int>();
        for (int j = 0; j < i; j++) {
            list->push_back(rand() % 1000);  // Random number between 0 and 999
        }

        // Sort the list
        auto start = chrono::high_resolution_clock::now();
        sort_wrapper(*list, algorithm, 0, list->size() - 1, show_state);
        auto end = chrono::high_resolution_clock::now();
        auto duration =
            chrono::duration_cast<chrono::microseconds>(end - start);

        averageTime += duration.count();

        // Print the number of elements of the list and the time it took to sort
        // it
        cout << i << "," << duration.count() << endl;

        // Delete the list
        delete list;
    }
    auto endAll = chrono::high_resolution_clock::now();

    // Average time: 0.0000000
    cout << endl
         << "Average time: " << averageTime / 1000 << " microseconds" << endl;

    // Total time: 0.0000000
    auto durationAll =
        chrono::duration_cast<chrono::microseconds>(endAll - startAll);
    cout << "Total time  : " << durationAll.count() << " microseconds" << endl
         << endl;
}

