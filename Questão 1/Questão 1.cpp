#include <iostream>
#include <stdio.h>
#include <string.h>
#define MAX_NOMES 1000
#define MAX_TAM 100

using namespace std;

void troca(char nome[][MAX_TAM], int a, int b) {
    char aux[MAX_TAM];
    strcpy(aux, nome[a]);
    strcpy(nome[a], nome[b]);
    strcpy(nome[b], aux);
}

void bubbleSort(char nomes[MAX_NOMES][MAX_TAM], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcmp(nomes[j], nomes[j + 1]) > 0) {
                troca(nomes, j, j + 1);
            }
        }
    }
}

void selectionSort(char nomes[MAX_NOMES][MAX_TAM], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(nomes[i], nomes[j]) > 0) {
                troca(nomes, i, j);
            }
        }
    }
}

void insertionSort(char nomes[MAX_NOMES][MAX_TAM], int n) {
    for (int i = 1; i < n; i++) {
        char aux[MAX_TAM];
        strcpy(aux, nomes[i]);
        int j = i - 1;
        while (j >= 0 && strcmp(aux, nomes[j]) < 0) {
            strcpy(nomes[j + 1], nomes[j]);
            j--;
        }
        strcpy(nomes[j + 1], aux);
    }
}

void merge(char nomes[MAX_NOMES][MAX_TAM], int start, int mid, int end) {
    char buffer[(end - start) + 1][MAX_TAM];
    int i = start, j = mid + 1, k = 0;

    while (i <= mid && j <= end) {
        if (strcmp(nomes[i], nomes[j]) < 0) {
            strcpy(buffer[k++], nomes[i++]);
        } else {
            strcpy(buffer[k++], nomes[j++]);
        }
    }
    while (i <= mid) {
        strcpy(buffer[k++], nomes[i++]);
    }
    while (j <= end) {
        strcpy(buffer[k++], nomes[j++]);
    }
    for (i = start, k = 0; i <= end; i++, k++) {
        strcpy(nomes[i], buffer[k]);
    }
}

void mergeSort(char nomes[MAX_NOMES][MAX_TAM], int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;
        mergeSort(nomes, start, mid);
        mergeSort(nomes, mid + 1, end);
        merge(nomes, start, mid, end);
    }
}

void imprimirVetor(char nomes[MAX_NOMES][MAX_TAM], int n) {
    for (int i = 0; i < n; i++) {
        cout << nomes[i] << endl;
    }
    cout << "\n";
}

int main(){
    FILE *arquivo = fopen("nomes2.txt", "r");

    if(arquivo == NULL){
        cout << "Erro ao tentar abrir arquivo.\n";
        return 0;
    }

    char nomes[MAX_NOMES][MAX_TAM];
    int i = 0;
    while(i < MAX_NOMES && fgets(nomes[i], MAX_TAM, arquivo)){
        nomes[i][strcspn(nomes[i], "\n")] = '\0';
        i++;
    }

    fclose(arquivo);

    int escolha;
    do{
        cout << "- - - Menu - - -\n\n";
        cout << "1 - Bubble\n";
        cout << "2 - Selection\n";
        cout << "3 - Insertion\n";
        cout << "4 - Merge Sort\n";
        cout << "5 - Sair\n";
        cin >> escolha;

        switch (escolha) {
            case 1:
                bubbleSort(nomes, i);
                cout << "\nBubble Sort:\n\n";
                imprimirVetor(nomes, i);
                break;
            case 2:
                selectionSort(nomes, i);
                cout << "\nSelection Sort:\n\n";
                imprimirVetor(nomes, i);
                break;
            case 3:
                insertionSort(nomes, i);
                cout << "\nInsertion Sort:\n\n";
                imprimirVetor(nomes, i);
                break;
            case 4:
                mergeSort(nomes, 0, i - 1);
                cout << "\nMerge Sort:\n\n";
                imprimirVetor(nomes, i);
                break;
            case 5:
                cout << "\nSaindo do programa.\n\n";
                break;
            default:
                cout << "\nEscolha inválida! Tente novamente.\n\n";
                break;
        }



    }while(escolha != 5);

    return 0;
}
