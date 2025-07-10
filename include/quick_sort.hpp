#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include "algoritmo_ordenacao.hpp"

class QuickSort : public AlgoritmoOrdenacao {
public:
    // Construtor
    QuickSort();

    // Implementação do método virtual puro
    void ordenar(vector<int>& vetor, Metricas& metricas) override;
};


#endif
