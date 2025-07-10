#ifndef ALGORITMO_ORDENACAO_HPP
#define ALGORITMO_ORDENACAO_HPP

#include <string>
#include <vector>
#include "metricas.hpp"

using namespace std;

class AlgoritmoOrdenacao {
    private:
        string nome;
        bool ativo;

    public:
        // Construtor que recebe o nome do algoritmo
        AlgoritmoOrdenacao(const string& nome);

        // Destrutor virtual (importante para polimorfismo)
        virtual ~AlgoritmoOrdenacao();

        // Método virtual puro (classe abstrata)
        virtual void ordenar(vector<int>& vetor, Metricas& metricas) = 0;

        // Métodos getters/setters
        string getNome() const;

        bool isAtivo() const;

        void setAtivo(bool status);
};

#endif