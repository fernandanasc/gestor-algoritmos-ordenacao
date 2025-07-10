#include "insertion_sort.hpp"

using namespace std;

// Construtor - chama o construtor da classe pai
InsertionSort::InsertionSort() : AlgoritmoOrdenacao("Insertion Sort") {
}

void InsertionSort::ordenar(vector<int>& vetor, Metricas& metricas) {
    size_t n = vetor.size();

    for (size_t i = 1; i < n; ++i) {
        int chave = vetor[i];
        size_t j = i;

        while (j > 0) {
            metricas.incrementarComparacoes();
            if (vetor[j - 1] > chave) {
                vetor[j] = vetor[j - 1];
                metricas.incrementarTrocas();
                j--;
            } else {
                break;
            }
        }

        // Se j != i, significa que houve pelo menos uma inserção
        if (j != i) {
            vetor[j] = chave;
            metricas.incrementarTrocas(); // Conta a inserção final como troca
            // Esta inserção final também deve ser contada como uma operação
        }
    }
}
