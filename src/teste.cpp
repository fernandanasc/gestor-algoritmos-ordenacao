#include "teste.hpp"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <iostream>

// Construtor
Teste::Teste(int id, const string& nome, const Vetor& v) 
    : id(id), nome(nome), vetor(v) {
}

// Métodos para executar algoritmos
void Teste::executarAlgoritmo(AlgoritmoOrdenacao* algo) {
    validarAlgoritmo(algo);
    
    // Verifica se já foi executado
    if (jaExecutou(algo->getNome())) {
        throw ExcecaoTeste("Algoritmo " + algo->getNome() + " já foi executado neste teste");
    }
    
    // Aviso para vetores grandes 
    size_t tamanho = vetor.getTamanho();
    if (tamanho >= 50000) {
        cout << "\n AVISO: Vetor grande (" << tamanho << " elementos). Aguarde...\n";
    }
    
    // Cria uma cópia do vetor para não alterar o original
    vector<int> vetorCopia = vetor.getCopia();
    
    // Cria métricas para este algoritmo
    Metricas metricas;
    
    // Mede o tempo de execução 
    auto inicio = chrono::high_resolution_clock::now();
    algo->ordenar(vetorCopia, metricas);
    auto fim = chrono::high_resolution_clock::now();
    
    // Calcula tempo em milissegundos
    double tempo = chrono::duration<double, milli>(fim - inicio).count();
    metricas.setTempo(tempo);
    
    // Cria e adiciona o resultado
    ResultadoTeste resultado(algo->getNome());
    resultado.setMetricas(metricas);
    
    // Exibe resultado usando o método toString() do ResultadoTeste
    cout << "\n" << resultado.toString() << "\n";
    
    adicionarResultado(resultado);
}

void Teste::executarTodosAlgoritmos(const vector<AlgoritmoOrdenacao*>& algos) {
    if (algos.empty()) {
        throw ExcecaoTeste("Lista de algoritmos esta vazia");
    }
    
    size_t tamanho = vetor.getTamanho();
    
    // Exibe informações do vetor 
    cout << "\n=== EXECUTANDO TESTE: " << nome << " ===\n";
    cout << "Tipo de vetor: " << vetor.getTipoString() << "\n";
    cout << "Tamanho: " << tamanho << " elementos\n";
    
    if (tamanho <= 100 && vetor.getTipo() != TipoVetor::ALEATORIO) {
        cout << "\nVetor original:\n";
        vetor.imprimir();
    } else if (vetor.getTipo() == TipoVetor::ALEATORIO) {
        cout << "\n(Vetor aleatório não exibido)\n";
    } else {
        cout << "\n(Vetor original não exibido: tamanho excede 100 elementos)\n";
    }
    
    // Executa cada algoritmo
    for (AlgoritmoOrdenacao* algo : algos) {
        if (algo != nullptr && !jaExecutou(algo->getNome())) {
            executarAlgoritmo(algo);
        }
    }
    
    // Mostra o melhor algoritmo
    if (!resultados.empty()) {
        try {
            auto melhor = getMelhorResultado();
            cout << "\n MELHOR ALGORITMO: " << melhor.getNomeAlgoritmo();
            cout << " (" << fixed << setprecision(3) << melhor.getMetricas().getTempo() << " ms)\n";
        } catch (const ExcecaoTeste&) {
            cout << "\nNenhum algoritmo executado com sucesso.\n";
        }
    }
}

void Teste::adicionarResultado(const ResultadoTeste& resultado) {
    resultados.push_back(resultado);
}

// Métodos de análise
ResultadoTeste Teste::getMelhorResultado() const {
    if (resultados.empty()) {
        throw ExcecaoTeste("Nenhum resultado disponível para análise");
    }
    
    ResultadoTeste melhor = resultados[0];
    for (const auto& resultado : resultados) {
        if (resultado.foiExecutado() && resultado < melhor) {
            melhor = resultado;
        }
    }
    
    if (!melhor.foiExecutado()) {
        throw ExcecaoTeste("Nenhum algoritmo foi executado com sucesso");
    }
    
    return melhor;
}

vector<ResultadoTeste> Teste::getResultadosOrdenados() const {
    vector<ResultadoTeste> ordenados;
    
    // Copia apenas resultados executados
    for (const auto& resultado : resultados) {
        if (resultado.foiExecutado()) {
            ordenados.push_back(resultado);
        }
    }
    
    // Ordena do melhor (menor tempo) para o pior
    sort(ordenados.begin(), ordenados.end());
    
    return ordenados;
}

// Getters
vector<ResultadoTeste> Teste::getResultados() const {
    return resultados;
}

int Teste::getId() const {
    return id;
}

string Teste::getNome() const {
    return nome;
}

Vetor Teste::getVetor() const {
    return vetor;
}

size_t Teste::getQuantidadeAlgoritmos() const {
    return resultados.size();
}

// Setters
void Teste::setNome(const string& novoNome) {
    nome = novoNome;
}

// Métodos de utilidade
string Teste::getRelatorio() const {
    stringstream ss;
    
    ss << "=== RELATORIO DO TESTE #" << id << " ===\n";
    ss << "Nome: " << nome << "\n";
    ss << "Vetor: " << vetor.getTipoString() << " (" << vetor.getTamanho() << " elementos)\n\n";
    
    if (resultados.empty()) {
        ss << "Nenhum algoritmo foi executado.\n";
        return ss.str();
    }
    
    // Mostra todos os resultados ordenados do melhor para o pior
    auto ordenados = getResultadosOrdenados();
    if (!ordenados.empty()) {
        ss << "RESULTADOS (ordenados por desempenho):\n\n";
        
        for (size_t i = 0; i < ordenados.size(); ++i) {
            const auto& resultado = ordenados[i];
            
            // Indicador de posição
            if (i == 0) {
                ss << "  MELHOR: ";
            } else if (i == 1) {
                ss << "  2 LUGAR: ";
            } else if (i == 2) {
                ss << "  3 LUGAR: ";
            } else {
                ss << " " << (i + 1) << " LUGAR: ";
            }
            
            // Nome do algoritmo
            ss << resultado.getNomeAlgoritmo() << "\n";
            
            // Métricas
            ss << "    Tempo: " << fixed << setprecision(3) << resultado.getMetricas().getTempo() << " ms\n";
            ss << "    Comparacoes: " << resultado.getMetricas().getComparacoes() << "\n";
            ss << "    Trocas: " << resultado.getMetricas().getTrocas() << "\n\n";
        }
    }
    
    return ss.str();
}

string Teste::getRelatorioResumido() const {
    stringstream ss;
    ss << "Teste #" << id << " - " << nome;
    ss << " (" << vetor.getTipoString() << ", " << vetor.getTamanho() << " elementos)";
    
    if (!resultados.empty()) {
        try {
            auto melhor = getMelhorResultado();
            ss << " - Melhor: " << melhor.getNomeAlgoritmo();
            ss << " (" << fixed << setprecision(2) << melhor.getMetricas().getTempo() << "ms)";
        } catch (const ExcecaoTeste&) {
            ss << " - Sem resultados validos";
        }
    }
    
    return ss.str();
}

void Teste::limparResultados() {
    resultados.clear();
}

bool Teste::temResultados() const {
    return !resultados.empty();
}

// Métodos de busca
ResultadoTeste* Teste::buscarResultado(const string& nomeAlgoritmo) {
    for (auto& resultado : resultados) {
        if (resultado.getNomeAlgoritmo() == nomeAlgoritmo) {
            return &resultado;
        }
    }
    return nullptr;
}

bool Teste::jaExecutou(const string& nomeAlgoritmo) const {
    for (const auto& resultado : resultados) {
        if (resultado.getNomeAlgoritmo() == nomeAlgoritmo) {
            return true;
        }
    }
    return false;
}

// Métodos auxiliares privados
void Teste::validarAlgoritmo(AlgoritmoOrdenacao* algo) {
    if (algo == nullptr) {
        throw ExcecaoTeste("Algoritmo nao pode ser nulo");
    }
}
