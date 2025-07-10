#include "quick_sort.hpp"

using namespace std;

static int particionar(vector<int>& vetor, int inicio, int fim, SortMetrics& metrics) {
    int pivo = vetor[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; ++j) {
        metrics.comparacoes++;
        if (vetor[j] < pivo) {
            i++;
            swap(vetor[i], vetor[j]);
            metrics.trocas++;
        }
    }

    swap(vetor[i + 1], vetor[fim]);
    metrics.trocas++;
    return i + 1;
}

static void quickSortRec(vector<int>& vetor, int inicio, int fim, SortMetrics& metrics) {
    if (inicio < fim) {
        int p = particionar(vetor, inicio, fim, metrics);
        quickSortRec(vetor, inicio, p - 1, metrics);
        quickSortRec(vetor, p + 1, fim, metrics);
    }
}

void quickSort(vector<int>& vetor, SortMetrics& metrics) {
    if (!vetor.empty()) {
        quickSortRec(vetor, 0, vetor.size() - 1, metrics);
    }
}
