#include "selection_sort.hpp"

using namespace std;

void selectionSort(vector<int>& vetor, SortMetrics& metrics) {
    size_t n = vetor.size();

    for (size_t i = 0; i < n - 1; ++i) {
        size_t indiceMin = i;

        for (size_t j = i + 1; j < n; ++j) {
            metrics.comparacoes++;
            if (vetor[j] < vetor[indiceMin]) {
                indiceMin = j;
            }
        }

        if (indiceMin != i) {
            swap(vetor[i], vetor[indiceMin]);
            metrics.trocas++;
        }
    }
}
