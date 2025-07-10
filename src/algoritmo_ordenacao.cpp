#include "algoritmo_ordenacao.hpp"

// Construtor
AlgoritmoOrdenacao::AlgoritmoOrdenacao(const string& nome) 
    : nome(nome), ativo(true) {
}

// Destrutor virtual
AlgoritmoOrdenacao::~AlgoritmoOrdenacao() {
    // Destrutor da classe base
}

// Getters/Setters
string AlgoritmoOrdenacao::getNome() const {
    return nome;
}

bool AlgoritmoOrdenacao::isAtivo() const {
    return ativo;
}

void AlgoritmoOrdenacao::setAtivo(bool status) {
    ativo = status;
}