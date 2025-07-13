#ifndef TESTE_HPP
#define TESTE_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include "vetor.hpp"
#include "resultado_teste.hpp"
#include "algoritmo_ordenacao.hpp"

using namespace std;

// Classe de exceção personalizada para erros de teste
class ExcecaoTeste : public exception {
private:
    string mensagem;

public:
    ExcecaoTeste(string msg) {
        mensagem = msg;
    }
    
    const char* what() const noexcept override {
        return mensagem.c_str();
    }
};

class Teste {
private:
    int id;
    string nome;
    string descricao;
    Vetor vetor;
    vector<ResultadoTeste> resultados;
    string dataHoraExecucao;
    bool concluido;

public:
    // Construtores
    Teste(int id, const string& nome, const Vetor& v);
    Teste(int id, const string& nome, const Vetor& v, const string& desc);

    // Métodos para executar algoritmos
    void executarAlgoritmo(AlgoritmoOrdenacao* algo);
    void executarTodosAlgoritmos(const vector<AlgoritmoOrdenacao*>& algos);
    void adicionarResultado(const ResultadoTeste& resultado);

    // Métodos de análise
    ResultadoTeste getMelhorResultado() const;
    vector<ResultadoTeste> getResultadosOrdenados() const; // Do melhor para o pior

    // Getters
    vector<ResultadoTeste> getResultados() const;
    int getId() const;
    string getNome() const;
    string getDescricao() const;
    Vetor getVetor() const;
    string getDataHoraExecucao() const;
    bool estaConcluido() const;
    size_t getQuantidadeAlgoritmos() const;

    // Setters
    void setNome(const string& novoNome);
    void setDescricao(const string& novaDesc);

    // Métodos de utilidade
    string getRelatorio() const;
    string getRelatorioResumido() const;
    void limparResultados();
    bool temResultados() const;

    // Métodos de busca
    ResultadoTeste* buscarResultado(const string& nomeAlgoritmo);
    bool jaExecutou(const string& nomeAlgoritmo) const;

private:
    // Métodos auxiliares privados
    void inicializarDataHora();
    void validarAlgoritmo(AlgoritmoOrdenacao* algo);
    void marcarComoConcluido();
};

#endif
