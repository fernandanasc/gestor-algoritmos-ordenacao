#include "algoritmo_ordenacao.hpp"

// Construtor
AlgoritmoOrdenacao::AlgoritmoOrdenacao(const string& nome) 
    : nome(nome) {
}

// Destrutor virtual
AlgoritmoOrdenacao::~AlgoritmoOrdenacao() {
    // Destrutor da classe base
}

// Getter
string AlgoritmoOrdenacao::getNome() const {
    return nome;
}