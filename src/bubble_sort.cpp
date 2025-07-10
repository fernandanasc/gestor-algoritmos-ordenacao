#include "bubble_sort.hpp"

using namespace std;

void bubbleSort(vector<int>& vetor, SortMetrics& metrics) {
    size_t n = vetor.size();
    bool trocou;

    for (size_t i = 0; i < n - 1; ++i) {
        trocou = false;

        for (size_t j = 0; j < n - i - 1; ++j) {
            metrics.comparacoes++;
            if (vetor[j] > vetor[j + 1]) {
                swap(vetor[j], vetor[j + 1]);
                metrics.trocas++;
                trocou = true;
            }
        }

        if (!trocou) break;
    }
}
