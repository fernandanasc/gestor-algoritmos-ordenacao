#include "bubble_sort.hpp"
#include <vector>

using namespace std;

// Construtor - chama o construtor da classe pai
BubbleSort::BubbleSort() : AlgoritmoOrdenacao("Bubble Sort") {
}

void BubbleSort::ordenar(vector<int>& vetor, Metricas& metricas) {
    size_t n = vetor.size();
    bool trocou;

    for (size_t i = 0; i < n - 1; ++i) {
        trocou = false;

        for (size_t j = 0; j < n - i - 1; ++j) {
            metricas.incrementarComparacoes();
            if (vetor[j] > vetor[j + 1]) {
                swap(vetor[j], vetor[j + 1]);
                metricas.incrementarTrocas();
                trocou = true;
            }
        }

        if (!trocou) break;
    }
}
