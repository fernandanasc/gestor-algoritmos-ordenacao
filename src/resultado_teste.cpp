#include "resultado_teste.hpp"
#include <sstream>
#include <iomanip>
#include <cmath>

// Construtor
ResultadoTeste::ResultadoTeste(const string& nome) 
    : nomeAlgoritmo(nome), executado(false) {
    // Métricas são inicializadas automaticamente com valores zero
}

// Métodos para definir dados
void ResultadoTeste::setMetricas(const Metricas& m) {
    metricas = m;
    executado = true; // Marca como executado quando define métricas
}

void ResultadoTeste::marcarExecutado() {
    executado = true;
}

// Getters
Metricas ResultadoTeste::getMetricas() const {
    return metricas;
}

string ResultadoTeste::getNomeAlgoritmo() const {
    return nomeAlgoritmo;
}

bool ResultadoTeste::foiExecutado() const {
    return executado;
}

// Métodos de análise

string ResultadoTeste::toString() const {
    if (!executado) {
        return nomeAlgoritmo + ": [Nao executado]";
    }
    
    stringstream ss;
    ss << fixed << setprecision(3);
    
    ss << "=== " << nomeAlgoritmo << " ===\n";
    ss << "Tempo: " << metricas.getTempo() << " ms\n";
    ss << "Comparacoes: " << metricas.getComparacoes() << "\n";
    ss << "Trocas: " << metricas.getTrocas();
    
    return ss.str();
}

// Operadores para comparação
bool ResultadoTeste::operator<(const ResultadoTeste& outro) const {
    // Só compara se ambos foram executados
    if (!this->executado || !outro.executado) {
        return false; // Não pode comparar
    }
    
    // 1º critério: Tempo (mais importante)
    double tempoThis = this->metricas.getTempo();
    double tempoOutro = outro.metricas.getTempo();
    
    // Se a diferença de tempo for significativa (mais de 1ms), usa o tempo
    if (abs(tempoThis - tempoOutro) > 1.0) {
        return tempoThis < tempoOutro; // Menor tempo = melhor
    }
    
    // 2º critério: Se tempos são parecidos, compara trocas
    size_t trocasThis = this->metricas.getTrocas();
    size_t trocasOutro = outro.metricas.getTrocas();
    
    if (trocasThis != trocasOutro) {
        return trocasThis < trocasOutro; // Menos trocas = melhor
    }
    
    // 3º critério: Se trocas são iguais, compara comparações
    size_t compThis = this->metricas.getComparacoes();
    size_t compOutro = outro.metricas.getComparacoes();
    
    return compThis < compOutro; // Menos comparações = melhor
}