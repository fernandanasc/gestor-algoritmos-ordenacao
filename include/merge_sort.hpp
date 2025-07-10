#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include "algoritmo_ordenacao.hpp"

class MergeSort : public AlgoritmoOrdenacao {
public:
    // Construtor
    MergeSort();

    // Implementação do método virtual puro
    void ordenar(vector<int>& vetor, Metricas& metricas) override;
};

#endif
