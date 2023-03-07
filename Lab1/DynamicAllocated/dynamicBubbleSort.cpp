// BubbleSort with doubly linked list

#include <iostream>
#include "list.cpp"
#include <chrono>

using namespace std;

void zeroSizeListError();
void stressMode();

int main(int argc, char *argv[]){
    char seeList, seeTime;
    srand(time(NULL));
    // if argv == "-stress", then the program will run in stress mode
    if (argc == 2 && string(argv[1]) == "-stress"){
        stressMode();
        return 0;
    }

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
            zeroSizeListError();
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

void stressMode(){
    // Generate 1000 random lists, each with a random number of random elements
    // Print the average time it took to sort all the lists

    auto startAll = chrono::high_resolution_clock::now();
    auto averageTime = 0;

    cout << "Number of elements,Time taken by the sorting function" << endl;

    // Generate 1000 random lists
    for (int i = 0; i < 1000; i++){
        int howManyNumbers = rand() % 1000 + 1;
        LinkedList *list = new LinkedList();

        // Generate a random number of elements
        for (int j = 0; j < howManyNumbers; j++){ list->add(rand() % 1000); }

        // Sort the list
        auto start = chrono::high_resolution_clock::now();
        list->bubbleSort(list->head, list->head->next, list->getSize(), 'n');
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        
        averageTime += duration.count();

        // Print the number of elements of the list and the time it took to sort it
        cout << howManyNumbers << "," << duration.count() << endl;

        // Delete the list
        delete list;
        list = nullptr;
    }
    auto endAll = chrono::high_resolution_clock::now();

    // Average time: 0.0000000
    cout << endl << "Average time: " << averageTime / 1000 << " microseconds" << endl;

    // Total time: 0.0000000
    auto durationAll = chrono::duration_cast<chrono::microseconds>(endAll - startAll);
    cout << "Total time  : " << durationAll.count() << " microseconds" << endl << endl;
}

// I know this is a bit stupid, but i was bored
void zeroSizeListError(){
    int error = rand() % 10;
    cout << endl;
    switch (error){
        case 0:
            cout << "Error: Sorting a zero-sized list is like trying to find love on a deserted island. Sure, you might think you have a chance at first, but as time goes on, you'll realize that you're just talking to yourself and the only thing you're going to end up with is a lonely segmentation fault. So please, add some elements to your list and find love elsewhere." << endl;
            break;
        case 1:
            cout << "Uh oh, it looks like your list has gone on a diet and is now zero-sized! Are you sure it's getting enough bytes to eat? Please feed it some data before attempting to sort." << endl;
            break;
        case 2:
            cout << "Warning: Sorting a zero-sized list is like trying to organize a party for no one. Eventually, you'll realize you're just talking to yourself and end up in a lonely segmentation fault. Please add some elements to your list before trying to sort it." << endl;
            break;
        case 3:
            cout << "Error: Trying to sort a zero-sized list is like trying to build a time machine out of a toaster. It might seem like a good idea in theory, but it's just not going to work. Trust us, we've been there before. We once tried to build a time machine out of a toaster, a blender, and a rubber duck, and it didn't end well. We ended up causing a rift in the space-time continuum and accidentally traveled back to the time of the dinosaurs. Needless to say, things got a bit messy. So please, learn from our mistake and add some elements to your list before attempting to sort it." << endl;
            break;
        case 4:
            cout << "Error: Sorting a zero-sized list is like trying to teach a goldfish how to play chess. Sure, you might have good intentions and want to teach your little aquatic friend a new skill, but it's just not going to happen. We once tried to teach a goldfish how to play chess, and let's just say it didn't go well. We ended up with a soggy chessboard and a very confused fish. So please, spare yourself the trouble and add some elements to your list before attempting to sort it." << endl;
            break;
        case 5:
            cout << "Oops! It looks like you're trying to sort a zero-sized list. While we appreciate your enthusiasm for sorting, we must remind you that trying to sort an empty list is like trying to bake a cake with no ingredients. So please, make sure your list has some elements before attempting to sort it." << endl;
            break;
        case 6:
            cout << "Error: What on earth are you thinking? Trying to sort a zero-sized list is an unholy practice that goes against the very laws of nature. We're talking sacrilege, blasphemy, and a whole lot of other words we can't say in a polite way. So please, for the sake of all that is good and right in this world, add some elements to your list before attempting to sort it. And don't ever, EVER try to sort a zero-sized list again." << endl;
            break;
        case 7:
            cout << "Verily I say unto thee, attempting to sort a zero-sized list is like sowing seed in barren soil. For as the seed falls upon the barren soil, so too shall thy attempt at sorting come to naught. Thy list shall remain unordered, and thou shalt be left with naught but a segmentation fault to mark thy efforts. For lo, it is not right to attempt to sort that which is void of substance, and such actions are not pleasing unto the gods of code. Therefore, add elements unto thy list before attempting to sort, and thy programming shall prospe" << endl;
            break;
        case 8:
            cout << "Wait a minute, what's going on here?" << endl <<
                    "This array seems to have disappeared" << endl <<
                    "It's not even there, not even a byte" << endl <<
                    "And now you want us to sort it just right?" << endl <<
                    endl <<
                    "We're not quite sure how to proceed" << endl <<
                    "For there's nothing here, no data to feed" << endl <<
                    "It's like asking us to paint the sky" << endl <<
                    "When there's no canvas, no paint to apply" << endl <<
                    endl <<
                    "Perhaps there's an error in the code" << endl <<
                    "And your array, it simply won't load" << endl <<
                    "Or maybe you're just having some fun" << endl <<
                    "And this is all a test, with nothing to be done" << endl <<
                    endl <<
                    "Either way, we can't sort what's not there" << endl <<
                    "So please ensure that your array is aware" << endl <<
                    "And has elements to sort and align" << endl <<
                    "Then we'll be happy to help, and all will be fine." << endl;
            break;
        case 9:
            cout << "How do you expect me to sort a list of size zero? I'm not a magician, you know. I can't just make elements appear out of thin air. I need data to work with, and right now, I don't have any. So please, add some elements to your list before attempting to sort it." << endl;
    }
}


// I hope it works
