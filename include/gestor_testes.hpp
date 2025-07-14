#ifndef GESTOR_TESTES_HPP
#define GESTOR_TESTES_HPP

#include <vector>
#include <string>
#include "teste.hpp"

using namespace std;

class GestorTestes {
private:
    vector<Teste> testes;
    int proximoId;

public:
    // Construtor
    GestorTestes();

    // CRUD - Create
    int criarTeste(const string& nome, const Vetor& vetor);

    // CRUD - Read
    Teste* buscarPorId(int id);

    // CRUD - Update
    bool editarTeste(int id, const string& novoNome);

    // CRUD - Delete
    bool removerTeste(int id);

    // Métodos de análise
    bool temTestes() const;

    // Métodos de utilidade
    void exibirLista() const;
    void exibirDetalhes(int id) const;

private:
    // Métodos auxiliares
    int gerarProximoId();
};

#endif
