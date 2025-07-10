#include "selection_sort.hpp"

// Construtor - chama o construtor da classe pai
SelectionSort::SelectionSort() : AlgoritmoOrdenacao("Selection Sort") {
}

// Implementação do método da classe (público)
void SelectionSort::ordenar(vector<int>& vetor, Metricas& metricas) {
    size_t n = vetor.size();

    for (size_t i = 0; i < n - 1; ++i) {
        size_t indiceMin = i;

        for (size_t j = i + 1; j < n; ++j) {
            metricas.incrementarComparacoes();
            if (vetor[j] < vetor[indiceMin]) {
                indiceMin = j;
            }
        }

        if (indiceMin != i) {
            swap(vetor[i], vetor[indiceMin]);
            metricas.incrementarTrocas();
        }
    }
}
