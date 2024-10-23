#include <stdio.h>
#include <string.h>
#include <iostream>

#define MAX_TIMES 12
#define MAX_TAM_NOME 50

using namespace std;

struct Time {
    char nome[MAX_TAM_NOME];
    int pontos = 0;
    int vitorias = 0;
    int empates = 0;
    int derrotas = 0;
    int golsPro = 0;
    int golsContra = 0;
    int saldoGols = 0;
};

void troca(Time &a, Time &b) {
    Time temp = a;
    a = b;
    b = temp;
}

void bubbleSort(Time* times, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (times[j].pontos < times[j + 1].pontos ||
                (times[j].pontos == times[j + 1].pontos && times[j].vitorias < times[j + 1].vitorias) ||
                (times[j].pontos == times[j + 1].pontos && times[j].vitorias == times[j + 1].vitorias && times[j].saldoGols < times[j + 1].saldoGols) ||
                (times[j].pontos == times[j + 1].pontos && times[j].vitorias == times[j + 1].vitorias && times[j].saldoGols == times[j + 1].saldoGols && times[j].golsPro < times[j + 1].golsPro)) {

                troca(times[j], times[j + 1]);
            }
        }
    }
}

void selectionSort(Time* times, int n) {
    for (int i = 0; i < n - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (times[j].pontos > times[maxIndex].pontos ||
                (times[j].pontos == times[maxIndex].pontos && times[j].vitorias > times[maxIndex].vitorias) ||
                (times[j].pontos == times[maxIndex].pontos && times[j].vitorias == times[maxIndex].vitorias && times[j].saldoGols > times[maxIndex].saldoGols) ||
                (times[j].pontos == times[maxIndex].pontos && times[j].vitorias == times[maxIndex].vitorias && times[j].saldoGols == times[maxIndex].saldoGols && times[j].golsPro > times[maxIndex].golsPro)) {
                maxIndex = j;
            }
        }

        if (maxIndex != i) {
            troca(times[i], times[maxIndex]);
        }
    }
}

void insertionSort(Time* times, int n) {
    for (int i = 1; i < n; i++) {
        Time key = times[i];
        int j = i - 1;
        while (j >= 0 && (key.pontos > times[j].pontos ||
                (key.pontos == times[j].pontos && key.vitorias > times[j].vitorias) ||
                (key.pontos == times[j].pontos && key.vitorias == times[j].vitorias && key.saldoGols > times[j].saldoGols) ||
                (key.pontos == times[j].pontos && key.vitorias == times[j].vitorias && key.saldoGols == times[j].saldoGols && key.golsPro > times[j].golsPro))) {
            times[j + 1] = times[j];
            j--;
        }
        times[j + 1] = key;
    }
}

void merge(Time* times, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Time* leftArr = new Time[n1];
    Time* rightArr = new Time[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = times[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = times[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i].pontos > rightArr[j].pontos ||
            (leftArr[i].pontos == rightArr[j].pontos && leftArr[i].vitorias > rightArr[j].vitorias) ||
            (leftArr[i].pontos == rightArr[j].pontos && leftArr[i].vitorias == rightArr[j].vitorias && leftArr[i].saldoGols > rightArr[j].saldoGols) ||
            (leftArr[i].pontos == rightArr[j].pontos && leftArr[i].vitorias == rightArr[j].vitorias && leftArr[i].saldoGols == rightArr[j].saldoGols && leftArr[i].golsPro > rightArr[j].golsPro)) {
            times[k++] = leftArr[i++];
        } else {
            times[k++] = rightArr[j++];
        }
    }

    while (i < n1) {
        times[k++] = leftArr[i++];
    }

    while (j < n2) {
        times[k++] = rightArr[j++];
    }

    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(Time* times, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(times, left, mid);
        mergeSort(times, mid + 1, right);
        merge(times, left, mid, right);
    }
}



bool compararTimes(char* time1, char* time2) {
    int i = 0;
    while (time1[i] != '\0' && time2[i] != '\0') {
        if (time1[i] != time2[i]) {
            return false;
        }
        i++;
    }

    return (time1[i] == '\0' && time2[i] == '\0');
}

void copiarTime(char* destino, char* origem) {
    int i = 0;
    while (origem[i] != '\0') {
        destino[i] = origem[i];
        i++;
    }
    destino[i] = '\0';
}

void processarJogo(char* linha, Time times[], int &qtdTimes) {
    char time1[MAX_TAM_NOME], time2[MAX_TAM_NOME];
    int gols1, gols2;

    sscanf(linha, "%s %dX%d %s", time1, &gols1, &gols2, time2);

    int index1 = -1, index2 = -1;
    for (int i = 0; i < qtdTimes; i++) {
        if (compararTimes(times[i].nome, time1)) index1 = i;
        if (compararTimes(times[i].nome, time2)) index2 = i;
    }

    if (index1 == -1) {
        copiarTime(times[qtdTimes].nome, time1);
        index1 = qtdTimes++;
    }
    if (index2 == -1) {
        copiarTime(times[qtdTimes].nome, time2);
        index2 = qtdTimes++;
    }

    times[index1].golsPro += gols1;
    times[index1].golsContra += gols2;
    times[index2].golsPro += gols2;
    times[index2].golsContra += gols1;

    times[index1].saldoGols = times[index1].golsPro - times[index1].golsContra;
    times[index2].saldoGols = times[index2].golsPro - times[index2].golsContra;

    if (gols1 > gols2) {
        times[index1].pontos += 3;
        times[index1].vitorias++;
        times[index2].derrotas++;
    } else if (gols1 < gols2) {
        times[index2].pontos += 3;
        times[index2].vitorias++;
        times[index1].derrotas++;
    } else {
        times[index1].pontos++;
        times[index2].pontos++;
        times[index1].empates++;
        times[index2].empates++;
    }
}

void imprimirTabela(Time* times, int qtdTimes) {
    cout << "Tabela do Campeonato:\n\n";

    for (int i = 0; i < qtdTimes; i++) {
        cout << "Time: " << times[i].nome << "\n";
        cout << "Pontos: " << times[i].pontos << "\n";
        cout << "Vitorias: " << times[i].vitorias << "\n";
        cout << "Empates: " << times[i].empates << "\n";
        cout << "Derrotas: " << times[i].derrotas << "\n";
        cout << "Saldo de Gols: " << times[i].saldoGols << "\n";
        cout << "Gols Pro: " << times[i].golsPro << "\n";
        cout << "Gols Contra: " << times[i].golsContra << "\n";
        cout << string(40, '-') << "\n";
    }
}

int main() {
    Time times[MAX_TIMES];
    int qtdTimes = 0;
    char linha[100];

    FILE *arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        cout << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    while (fgets(linha, sizeof(linha), arquivo)) {
        processarJogo(linha, times, qtdTimes);
    }

    fclose(arquivo);

    int escolha;
    do {
        cout << "- - - Menu - - -\n";
        cout << "1 - Bubble\n";
        cout << "2 - Selection\n";
        cout << "3 - Insertion\n";
        cout << "4 - Merge Sort\n";
        cout << "5 - Sair\n";
        cin >> escolha;

        switch(escolha) {
            case 1:
                bubbleSort(times, qtdTimes);
                imprimirTabela(times, qtdTimes);
                break;
            case 2:
                selectionSort(times, qtdTimes);
                imprimirTabela(times, qtdTimes);
                break;
            case 3:
                insertionSort(times, qtdTimes);
                imprimirTabela(times, qtdTimes);
                break;
            case 4:
                mergeSort(times, 0, qtdTimes - 1);
                imprimirTabela(times, qtdTimes);
                break;
        }
    } while (escolha != 5);

    return 0;
}
