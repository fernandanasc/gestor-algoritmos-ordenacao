#include "teste.hpp"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <iostream>

// Construtor simples
Teste::Teste(int id, const string& nome, const Vetor& v) 
    : id(id), nome(nome), vetor(v), concluido(false) {
    // descrição fica vazia
    inicializarDataHora();
}

// Construtor com descrição
Teste::Teste(int id, const string& nome, const Vetor& v, const string& desc)
    : id(id), nome(nome), descricao(desc), vetor(v), concluido(false) {
    inicializarDataHora();
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
        cout << "\n⚠️  AVISO: Vetor grande (" << tamanho << " elementos). Aguarde...\n";
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
    
    // Exibe resultado individual
    cout << "=== " << algo->getNome() << " ===" << endl;
    cout << fixed << setprecision(3);
    cout << "Tempo: " << tempo << " ms" << endl;
    cout << "Comparações: " << metricas.getComparacoes() << endl;
    cout << "Trocas: " << metricas.getTrocas() << endl << endl;
    
    // Cria e adiciona o resultado
    ResultadoTeste resultado(algo->getNome());
    resultado.setMetricas(metricas);
    
    adicionarResultado(resultado);
}

void Teste::executarTodosAlgoritmos(const vector<AlgoritmoOrdenacao*>& algos) {
    if (algos.empty()) {
        throw ExcecaoTeste("Lista de algoritmos está vazia");
    }
    
    size_t tamanho = vetor.getTamanho();
    
    // Exibe informações do vetor 
    cout << "\n=== EXECUTANDO TESTE: " << nome << " ===\n";
    cout << "Tipo de vetor: " << vetor.getTipoString() << "\n";
    cout << "Tamanho: " << tamanho << " elementos\n";
    
    if (tamanho <= 100) {
        cout << "\nVetor original:\n";
        vetor.imprimir();
    } else {
        cout << "\n(Vetor original não exibido: tamanho excede 100 elementos)\n";
    }
    
    // Executa cada algoritmo
    for (AlgoritmoOrdenacao* algo : algos) {
        if (algo != nullptr && algo->isAtivo() && !jaExecutou(algo->getNome())) {
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
    
    marcarComoConcluido();
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

string Teste::getDescricao() const {
    return descricao;
}

Vetor Teste::getVetor() const {
    return vetor;
}

string Teste::getDataHoraExecucao() const {
    return dataHoraExecucao;
}

bool Teste::estaConcluido() const {
    return concluido;
}

size_t Teste::getQuantidadeAlgoritmos() const {
    return resultados.size();
}

// Setters
void Teste::setNome(const string& novoNome) {
    nome = novoNome;
}

void Teste::setDescricao(const string& novaDesc) {
    descricao = novaDesc;
}

// Métodos de utilidade
string Teste::getRelatorio() const {
    stringstream ss;
    
    ss << "=== RELATÓRIO DO TESTE #" << id << " ===\n";
    ss << "Nome: " << nome << "\n";
    if (!descricao.empty()) {
        ss << "Descrição: " << descricao << "\n";
    }
    ss << "Vetor: " << vetor.getTipoString() << " (" << vetor.getTamanho() << " elementos)\n";
    ss << "Status: " << (concluido ? "Concluído" : "Em andamento") << "\n\n";
    
    if (resultados.empty()) {
        ss << "Nenhum algoritmo foi executado.\n";
        return ss.str();
    }
    
    // Mostra apenas o melhor resultado
    auto ordenados = getResultadosOrdenados();
    if (!ordenados.empty()) {
        ss << "🏆 MELHOR: " << ordenados[0].getNomeAlgoritmo() << "\n";
        ss << "   Tempo: " << fixed << setprecision(3) << ordenados[0].getMetricas().getTempo() << " ms\n";
        ss << "   Total executados: " << ordenados.size() << " algoritmos\n";
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
            ss << " - Sem resultados válidos";
        }
    }
    
    return ss.str();
}

void Teste::limparResultados() {
    resultados.clear();
    concluido = false;
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
void Teste::inicializarDataHora() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_mday << "/"
       << setw(2) << (1 + ltm->tm_mon) << "/"
       << (1900 + ltm->tm_year) << " "
       << setw(2) << ltm->tm_hour << ":"
       << setw(2) << ltm->tm_min << ":"
       << setw(2) << ltm->tm_sec;
    
    dataHoraExecucao = ss.str();
}

void Teste::validarAlgoritmo(AlgoritmoOrdenacao* algo) {
    if (algo == nullptr) {
        throw ExcecaoTeste("Algoritmo não pode ser nulo");
    }
    if (!algo->isAtivo()) {
        throw ExcecaoTeste("Algoritmo " + algo->getNome() + " está inativo");
    }
}

void Teste::marcarComoConcluido() {
    concluido = true;
}
