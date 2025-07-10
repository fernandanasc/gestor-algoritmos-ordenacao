#ifndef INSERTION_SORT_HPP
#define INSERTION_SORT_HPP

#include "algoritmo_ordenacao.hpp"

class InsertionSort : public AlgoritmoOrdenacao {
public:
    // Construtor
    InsertionSort();

    // Implementação do método virtual puro
    void ordenar(vector<int>& vetor, Metricas& metricas) override;
};

#endif