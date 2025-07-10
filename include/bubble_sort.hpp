#ifndef BUBBLE_SORT_HPP
#define BUBBLE_SORT_HPP

#include "algoritmo_ordenacao.hpp"

class BubbleSort : public AlgoritmoOrdenacao {
public:
    // Construtor
    BubbleSort();
    
    // Implementação do método virtual puro
    void ordenar(vector<int>& vetor, Metricas& metricas) override;
};

#endif