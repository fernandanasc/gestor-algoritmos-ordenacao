#ifndef METRICAS_HPP
#define METRICAS_HPP

#include <string>

using namespace std;

class Metricas {
private:
    size_t comparacoes;
    size_t trocas;
    double tempoExecucao;

public:
    // Construtor
    Metricas();
    
    // Métodos para resetar
    void reset();
    
    // Métodos para incrementar
    void incrementarComparacoes();
    void incrementarTrocas();
    
    // Método para definir tempo
    void setTempo(double tempo);
    
    // Getters
    size_t getComparacoes() const;
    size_t getTrocas() const;
    double getTempo() const;
    
    // Método para exibir
    string toString() const;
};

#endif
