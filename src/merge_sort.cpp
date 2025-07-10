#include "merge_sort.hpp"

// Construtor - chama o construtor da classe pai
MergeSort::MergeSort() : AlgoritmoOrdenacao("Merge Sort") {
}

// Função auxiliar para fazer o merge (privada da implementação)
void merge(vector<int>& vetor, int inicio, int meio, int fim, Metricas& metricas) {
    vector<int> esquerda(vetor.begin() + inicio, vetor.begin() + meio + 1);
    vector<int> direita(vetor.begin() + meio + 1, vetor.begin() + fim + 1);

    size_t i = 0, j = 0;
    int k = inicio;

    while (i < esquerda.size() && j < direita.size()) {
        metricas.incrementarComparacoes();
        if (esquerda[i] <= direita[j]) {
            vetor[k++] = esquerda[i++];
        } else {
            vetor[k++] = direita[j++];
        }
        metricas.incrementarTrocas(); // Conta toda escrita como uma troca
    }

    while (i < esquerda.size()) {
        vetor[k++] = esquerda[i++];
        metricas.incrementarTrocas();
    }

    while (j < direita.size()) {
        vetor[k++] = direita[j++];
        metricas.incrementarTrocas();
    }
}

// Função auxiliar recursiva
void mergeSortRec(vector<int>& vetor, int inicio, int fim, Metricas& metricas) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        mergeSortRec(vetor, inicio, meio, metricas);
        mergeSortRec(vetor, meio + 1, fim, metricas);
        merge(vetor, inicio, meio, fim, metricas);
    }
}

// Implementação do método da classe (público)
void MergeSort::ordenar(vector<int>& vetor, Metricas& metricas) {
    if (!vetor.empty()) {
        mergeSortRec(vetor, 0, vetor.size() - 1, metricas);
    }
}
