#ifndef RESULTADO_TESTE_HPP
#define RESULTADO_TESTE_HPP

#include <string>
#include "metricas.hpp"

using namespace std;

class ResultadoTeste {
private:
    string nomeAlgoritmo;
    Metricas metricas;
    bool executado;

public:
    // Construtor
    ResultadoTeste(const string& nome);

    // Método para definir os daddos do teste
    void setMetricas(const Metricas& m);
    void marcarExecutado();

    // Getters
    Metricas getMetricas() const;
    string getNomeAlgoritmo() const;
    bool foiExecutado() const;

    //Métodos de análise
    double getEficiencia() const; // Baseado no tempo (menor = melhor)
    string toString() const; // Para exibição formatada

    // Operadores para comparação
    bool operator<(const ResultadoTeste& outro) const; //Para encontrar o melhor (menor tempo)
    bool operator>(const ResultadoTeste& outro) const;
    bool operator==(const ResultadoTeste& outro) const;

};

#endif