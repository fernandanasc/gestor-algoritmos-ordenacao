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
double ResultadoTeste::getEficiencia() const {
    if (!executado) {
        return -1.0; // Valor inválido para não executado
    }
    return metricas.getTempo(); // Menor tempo = mais eficiente
}

string ResultadoTeste::toString() const {
    if (!executado) {
        return nomeAlgoritmo + ": [Não executado]";
    }
    
    stringstream ss;
    ss << fixed << setprecision(4);
    
    ss << nomeAlgoritmo << ":\n";
    ss << "  Tempo: " << metricas.getTempo() << " ms\n";
    ss << "  Comparações: " << metricas.getComparacoes() << "\n";
    ss << "  Trocas: " << metricas.getTrocas();
    
    return ss.str();
}

// Operadores para comparação
bool ResultadoTeste::operator<(const ResultadoTeste& outro) const {
    // Só compara se ambos foram executados
    if (!this->executado || !outro.executado) {
        return false; // Não pode comparar
    }
    
    // Menor tempo = melhor (mais eficiente)
    return this->metricas.getTempo() < outro.metricas.getTempo();
}

bool ResultadoTeste::operator>(const ResultadoTeste& outro) const {
    return outro < *this; // Reutiliza o operador <
}

bool ResultadoTeste::operator==(const ResultadoTeste& outro) const {
    if (!this->executado || !outro.executado) {
        return false; // Não pode comparar
    }
    
    // Tempos muito próximos = iguais
    double diferenca = abs(this->metricas.getTempo() - outro.metricas.getTempo());
    return diferenca < 0.0001; // Diferença menor que 0.0001ms = iguais
}