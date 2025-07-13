#ifndef VETOR_HPP
#define VETOR_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

// Enum para tipos de vetor
enum class TipoVetor {
    ALEATORIO,
    QUASE_ORDENADO,
    INVERSO,
    MANUAL
};

// Classe de exceção personalizada para erros de vetor
class ExcecaoVetor : public exception {
private:
    string mensagem;

public:
    ExcecaoVetor(const string& msg) : mensagem(msg) {}
    const char* what() const noexcept override {
        return mensagem.c_str();
    }
};

class Vetor {
private:
    vector<int> dados;
    size_t tamanho;
    TipoVetor tipo;

public:
    // Construtores
    Vetor(); // Construtor padrão (vetor vazio)
    Vetor(const vector<int>& dadosUsuario); // Construtor para vetor manual
    Vetor(size_t tam, TipoVetor t); // Construtor para vetor automático

    // Métodos para gerar vetores
    void gerar(size_t tam, TipoVetor t);
    void setDadosManual(const vector<int>& dadosUsuario);

    // Getters
    vector<int> getDados() const;
    vector<int> getCopia() const; // Retorna uma cópia para não alterar o original
    size_t getTamanho() const;
    TipoVetor getTipo() const;
    string getTipoString() const; // Converte TipoVetor para string
    bool ehManual() const;

    // Métodos de utilidade
    void imprimir() const;
    void validar(); // Valida se o vetor está correto
    bool estaVazio() const;

private:
    // Métodos auxiliares privados
    void validarTamanho(size_t tam);
    void gerarVetorAleatorio(size_t tam);
    void gerarVetorQuaseOrdenado(size_t tam);
    void gerarVetorInverso(size_t tam);
};

#endif