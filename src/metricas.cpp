#include "metricas.hpp"
#include <sstream>

// Construtor
Metricas::Metricas() : comparacoes(0), trocas(0), tempoExecucao(0.0) {
}

// Reset dos contadores
void Metricas::reset() {
    comparacoes = 0;
    trocas = 0;
    tempoExecucao = 0.0;
}

// Incrementar comparações
void Metricas::incrementarComparacoes() {
    comparacoes++;
}

// Incrementar trocas
void Metricas::incrementarTrocas() {
    trocas++;
}

// Definir tempo de execução
void Metricas::setTempo(double tempo) {
    tempoExecucao = tempo;
}

// Getters
size_t Metricas::getComparacoes() const {
    return comparacoes;
}

size_t Metricas::getTrocas() const {
    return trocas;
}

double Metricas::getTempo() const {
    return tempoExecucao;
}
