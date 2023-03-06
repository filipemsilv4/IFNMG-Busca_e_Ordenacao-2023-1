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
        
        LinkedList(){
            head = NULL;
            tail = NULL;
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
            }
            else{
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

        void bubbleSort(){
            printf("size: %d\n", getSize());
            Node *auxPrimary   = head;
            Node *auxSecondary = head->next;
            int size = getSize();

            for (int i = 0; i < size - 1; i++){
                auxPrimary = head;
                auxSecondary = head->next;
                for (int j = 0; j < size - i - 1; j++){
                    if (auxPrimary->val > auxSecondary->val){
                        swap(auxPrimary, auxSecondary);
                    }
                    auxPrimary = auxSecondary;
                    auxSecondary = auxSecondary->next;
                }
            }
        }

        // Recursive Faster Bubble Sort
        void recursiveFasterBubbleSort(Node *auxPrimary, Node *auxSecondary, int pos){
            printf("------------------------\n");
            // if the array is empty or has only one element, it is sorted
            if (pos == 1){ return; }

            // we will skip the already sorted elements, reducing the size of the array
            int newSize = pos;

            // if no swap is made, the array is sorted
            bool swapped = false;

            for (int j = 0; j < newSize - 1; j++){
                if (auxPrimary->val > auxSecondary->val){
                    swap(auxPrimary, auxSecondary);
                    swapped = true;
                    print();
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

            // sort the remaining array
            recursiveFasterBubbleSort(auxPrimary, auxSecondary, newSize);
        }
};