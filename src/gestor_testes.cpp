#include "gestor_testes.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

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
bool GestorTestes::editarTeste(int id, const string& novoNome) {
    Teste* teste = buscarPorId(id);
    if (teste != nullptr) {
        teste->setNome(novoNome);
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
    cout << "ID | Nome                     | Vetor                | Resultado\n";
    cout << "---|--------------------------|----------------------|-------------------------\n";
    
    for (const auto& teste : testes) {
        cout << setw(2) << teste.getId() << " | ";
        cout << setw(24) << left << teste.getNome() << " | ";
        cout << setw(20) << left << (teste.getVetor().getTipoString() + " (" + to_string(teste.getVetor().getTamanho()) + ")") << " | ";
        
        // Determinar o que mostrar na coluna Resultado
        if (!teste.temResultados()) {
            cout << "Nao executado";
        } else {
            auto resultados = teste.getResultados();
            if (resultados.size() == 1) {
                // Apenas um algoritmo executado
                cout << "Executado: " << resultados[0].getNomeAlgoritmo();
            } else {
                // Múltiplos algoritmos - mostrar o melhor
                try {
                    auto melhor = teste.getMelhorResultado();
                    cout << "Melhor: " << melhor.getNomeAlgoritmo() 
                         << " (" << fixed << setprecision(2) << melhor.getMetricas().getTempo() << "ms)";
                } catch (const exception&) {
                    cout << "Erro na analise";
                }
            }
        }
        cout << "\n";
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
        cout << "\nTeste com ID " << id << " nao encontrado.\n";
        return;
    }
    
    cout << teste->getRelatorio() << "\n";
}

// Métodos auxiliares privados
int GestorTestes::gerarProximoId() {
    return proximoId++;
}
