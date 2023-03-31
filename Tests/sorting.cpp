// Some sorting algorithms

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void){

}

// SelectionSort pseudocodigo
// percorrer o vetor inteiro
//      para cada elemento, percorrer o vetor inteiro
//          se o elemento atual for menor que o menor elemento
//              menor = atual
//      trocar o menor elemento com o elemento atual

void selectionSort(int L[], int n){
    for(int i = 0; i < n - 1; i++){ // Percorre o vetor
        int menor = i; // Índice do menor elemento
        for(int j = i + 1; j < n; j++){ // Percorre o vetor
            if(L[j] < L[menor]){ // Se o elemento atual for menor que o menor elemento
                menor = j; // Atualiza o índice do menor elemento
            }
        }
        swap(L[i], L[menor]); // Troca o menor elemento com o elemento atual
    }
}

// InsertionSort pseudocodigo
// percorrer o vetor inteiro
//      para cada elemento, percorrer o vetor até encontrar o elemento anterior
//          se o elemento anterior for maior que o elemento atual
//              mover o elemento anterior para a direita
//      inserir o elemento atual na posição correta
void insertionSort(int L[], int n){
    for(int i = 1; i < n; i++){ // Percorre o vetor
        int j = i - 1; // Índice do elemento anterior
        int valor = L[i]; // Valor a ser inserido
        while(j >= 0 && L[j] > valor){ // Enquanto o elemento anterior for maior que o valor a ser inserido
            L[j + 1] = L[j]; // Move o elemento para a direita
            j--; // Decrementa o índice
        }
        L[j + 1] = valor; // Insere o valor na posição correta
    }
}

// BubbleSort pseudocodigo
// percorrer o vetor inteiro
//      para cada elemento, percorrer o vetor até encontrar o elemento anterior
//          se o elemento anterior for maior que o elemento atual
//              trocar os elementos
//      se não houver trocas, parar
void bubbleSort(int L[], int n){
    bool swapped = true;
    int n2 = n;
    int aux = n - 1;
    while(swapped){ // Enquanto houver trocas
        swapped = false;
        for(int j = 0; j <= n2 - 2; j++){ // Percorre o vetor
            if(L[j] > L[j + 1]){ // Se o elemento atual for maior que o próximo
                swapped = true; // Marca que houve troca
                aux = j; // Guarda a posição do último elemento trocado
                swap(L[j], L[j + 1]); // Troca os elementos
            }
        }
        n2 = aux + 1; // Atualiza o tamanho do vetor
    }
}