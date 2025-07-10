#include "merge_sort.hpp"

using namespace std;

static void mergeSort(vector<int>& vetor, int inicio, int meio, int fim, SortMetrics& metrics) {
    vector<int> esquerda(vetor.begin() + inicio, vetor.begin() + meio + 1);
    vector<int> direita(vetor.begin() + meio + 1, vetor.begin() + fim + 1);

    size_t i = 0, j = 0;
    int k = inicio;

    while (i < esquerda.size() && j < direita.size()) {
        metrics.comparacoes++;
        if (esquerda[i] <= direita[j]) {
            vetor[k++] = esquerda[i++];
        } else {
            vetor[k++] = direita[j++];
        }
        metrics.trocas++; // Conta toda escrita como uma troca
    }

    while (i < esquerda.size()) {
        vetor[k++] = esquerda[i++];
        metrics.trocas++;

    }

    while (j < direita.size()) {
        vetor[k++] = direita[j++];
        metrics.trocas++;

    }
}

static void mergeSortRec(vector<int>& vetor, int inicio, int fim, SortMetrics& metrics) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        mergeSortRec(vetor, inicio, meio, metrics);
        mergeSortRec(vetor, meio + 1, fim, metrics);
        mergeSort(vetor, inicio, meio, fim, metrics);
    }
}

void mergeSort(vector<int>& vetor, SortMetrics& metrics) {
    if (!vetor.empty()) {
        mergeSortRec(vetor, 0, vetor.size() - 1, metrics);
    }
}
