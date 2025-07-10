#include "insertion_sort.hpp"

using namespace std;

void insertionSort(vector<int>& vetor, SortMetrics& metrics) {
    size_t n = vetor.size();

    for (size_t i = 1; i < n; ++i) {
        int chave = vetor[i];
        size_t j = i;

        while (j > 0) {
            metrics.comparacoes++;
            if (vetor[j - 1] > chave) {
                vetor[j] = vetor[j - 1];
                metrics.trocas++;
                j--;
            } else {
                break;
            }
        }

        // Se j != i, significa que houve pelo menos uma inserção
        if (j != i) {
            vetor[j] = chave;
            metrics.trocas++; // Conta a inserção final como troca
            // Esta inserção final também deve ser contada como uma operação
        }
    }
}
