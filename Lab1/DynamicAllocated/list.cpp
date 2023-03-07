#include <iostream>
#include <cstdlib>

using namespace std;

class Node{
    public:
        int val;
        Node* next;
        Node* prev;
};

class LinkedList{
    public:
        Node* head;
        Node* tail;
        int size;
        
        // Constructor
        LinkedList(){
            head = NULL;
            tail = NULL;
            size = 0;
        }

        // Destructor
        ~LinkedList(){
            Node* temp = head;
            while(temp != NULL){
                Node* next = temp->next;
                delete temp;
                temp = next;
            }
            size = 0;
        }

        void add(int val){
            Node* temp = new Node;
            temp->val = val;
            temp->next = NULL;
            temp->prev = NULL;
            if(head == NULL){
                head = temp;
                tail = temp;
            } else{
                tail->next = temp;
                temp->prev = tail;
                tail = temp;
            }
            size++;
        }

        void print(){
            Node* temp = head;
            while(temp != NULL){
                cout << temp->val << " ";
                temp = temp->next;
            }
            cout << endl;
        }

        int getSize(){ return size; }

        void swap(Node *node1, Node *node2){
            int temp   = node1->val;
            node1->val = node2->val;
            node2->val = temp;
        }

        // Recursive Faster Bubble Sort
        void bubbleSort(Node *auxPrimary, Node *auxSecondary, int pos, char seeList){
            // if the array is empty or has only one element, it is sorted
            if (pos <= 1){ return; }

            // we will skip the already sorted elements, reducing the size of the array
            int newSize = pos;

            bool swapped = false;

            // iterate through the array
            for (int j = 0; j < newSize - 1; j++){
                if (auxPrimary->val > auxSecondary->val){
                    swap(auxPrimary, auxSecondary);
                    swapped = true;
                }
                auxPrimary   = auxSecondary;
                auxSecondary = auxSecondary->next;
            }

            // if no swap is made, the array is sorted
            if (!swapped){ return; }

            // the last element is sorted, so we can skip it
            newSize--;

            // reset the pointers
            auxPrimary   = head;
            auxSecondary = head->next;

            if (seeList == 'y'){
                cout << "----== Iteration " << getSize() - pos + 1 << " ==----" << endl;
                print();
            }

            // sort the remaining array
            bubbleSort(auxPrimary, auxSecondary, newSize, seeList);
        }
};