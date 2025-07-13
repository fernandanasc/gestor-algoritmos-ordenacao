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
    int criarTeste(const string& nome, const Vetor& vetor, const string& descricao);

    // CRUD - Read
    Teste* buscarPorId(int id);

    // CRUD - Update
    bool editarTeste(int id, const string& novoNome, const string& novaDescricao = "");

    // CRUD - Delete
    bool removerTeste(int id);

    // Métodos de análise
    size_t getTotalTestes() const;
    bool temTestes() const;

    // Métodos de utilidade
    void exibirLista() const;
    void exibirDetalhes(int id) const;

private:
    // Métodos auxiliares
    int gerarProximoId();
};

#endif
