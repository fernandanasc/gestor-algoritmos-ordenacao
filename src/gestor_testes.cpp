#include "gestor_testes.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

// Construtor
GestorTestes::GestorTestes() : proximoId(1) {
    // Vector já é inicializado vazio
}

// CRUD - Create
int GestorTestes::criarTeste(const string& nome, const Vetor& vetor) {
    int id = gerarProximoId();
    testes.emplace_back(id, nome, vetor);
    return id;
}

int GestorTestes::criarTeste(const string& nome, const Vetor& vetor, const string& descricao) {
    int id = gerarProximoId();
    testes.emplace_back(id, nome, vetor, descricao);
    return id;
}

// CRUD - Read
Teste* GestorTestes::buscarPorId(int id) {
    for (auto& teste : testes) {
        if (teste.getId() == id) {
            return &teste;
        }
    }
    return nullptr;
}

// CRUD - Update
bool GestorTestes::editarTeste(int id, const string& novoNome, const string& novaDescricao) {
    Teste* teste = buscarPorId(id);
    if (teste != nullptr) {
        teste->setNome(novoNome);
        if (!novaDescricao.empty()) {
            teste->setDescricao(novaDescricao);
        }
        return true;
    }
    return false;
}

// CRUD - Delete
bool GestorTestes::removerTeste(int id) {
    auto it = find_if(testes.begin(), testes.end(), 
                      [id](const Teste& t) { return t.getId() == id; });
    
    if (it != testes.end()) {
        testes.erase(it);
        return true;
    }
    return false;
}

// Métodos de análise
size_t GestorTestes::getTotalTestes() const {
    return testes.size();
}

bool GestorTestes::temTestes() const {
    return !testes.empty();
}

// Métodos de utilidade
void GestorTestes::exibirLista() const {
    if (testes.empty()) {
        cout << "\nNenhum teste cadastrado.\n";
        return;
    }
    
    cout << "\n=== LISTA DE TESTES ===\n";
    for (const auto& teste : testes) {
        cout << "ID: " << teste.getId() 
             << " | Nome: " << teste.getNome()
             << " | Vetor: " << teste.getVetor().getTipoString() 
             << " (" << teste.getVetor().getTamanho() << " elementos)"
             << " | Status: " << (teste.estaConcluido() ? "Concluído" : "Pendente")
             << "\n";
    }
}

void GestorTestes::exibirDetalhes(int id) const {
    // Busca manual já que não temos versão const
    const Teste* teste = nullptr;
    for (const auto& t : testes) {
        if (t.getId() == id) {
            teste = &t;
            break;
        }
    }
    
    if (teste == nullptr) {
        cout << "\nTeste com ID " << id << " não encontrado.\n";
        return;
    }
    
    cout << teste->getRelatorio() << "\n";
}

// Métodos auxiliares privados
int GestorTestes::gerarProximoId() {
    return proximoId++;
}
