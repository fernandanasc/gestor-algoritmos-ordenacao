#include "quick_sort.hpp"

// Construtor - chama o construtor da classe pai
QuickSort::QuickSort() : AlgoritmoOrdenacao("Quick Sort") {
}

// Função auxiliar para particionar
int particionar(vector<int>& vetor, int inicio, int fim, Metricas& metricas) {
    int pivo = vetor[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; ++j) {
        metricas.incrementarComparacoes();
        if (vetor[j] < pivo) {
            i++;
            swap(vetor[i], vetor[j]);
            metricas.incrementarTrocas();
        }
    }

    swap(vetor[i + 1], vetor[fim]);
    metricas.incrementarTrocas();
    return i + 1;
}

// Função auxiliar recursiva
void quickSortRec(vector<int>& vetor, int inicio, int fim, Metricas& metricas) {
    if (inicio < fim) {
        int p = particionar(vetor, inicio, fim, metricas);
        quickSortRec(vetor, inicio, p - 1, metricas);
        quickSortRec(vetor, p + 1, fim, metricas);
    }
}

// Implementação do método da classe (público)
void QuickSort::ordenar(vector<int>& vetor, Metricas& metricas) {
    if (!vetor.empty()) {
        quickSortRec(vetor, 0, vetor.size() - 1, metricas);
    }
}
