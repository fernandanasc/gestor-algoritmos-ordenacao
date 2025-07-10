#ifndef SELECTION_SORT_HPP
#define SELECTION_SORT_HPP

#include "algoritmo_ordenacao.hpp"

class SelectionSort : public AlgoritmoOrdenacao {
public:
    // Construtor
    SelectionSort();

    // Implementação do método virtual puro
    void ordenar(vector<int>& vetor, Metricas& metricas) override;
};

#endif
