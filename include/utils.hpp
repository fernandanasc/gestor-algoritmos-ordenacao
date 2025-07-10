#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>
#include <functional>
#include <iostream>
#include <fstream>

using namespace std;

enum class TipoVetor {
    ALEATORIO,
    QUASE_ORDENADO,
    INVERSO
};

struct SortMetrics {
    size_t comparacoes = 0;
    size_t trocas = 0;
};

vector<int> gerarVetor(size_t tamanho, TipoVetor tipo);

void imprimirVetor(const vector<int>& v);

// Função template para medir tempo de execução (em milissegundos)
template<typename Func>
double medirTempo(Func func) {
    auto inicio = chrono::high_resolution_clock::now();
    func();
    auto fim = chrono::high_resolution_clock::now();
    return chrono::duration<double, milli>(fim - inicio).count();
}

bool desejaContinuar();

// Estrutura para armazenar dados de teste
struct TestData {
    string algoritmo;
    string tipoVetor;
    size_t tamanho;
    double tempo;
    size_t comparacoes;
    size_t trocas;
};

// Funções para exportação CSV
void exportarDadosCompletos();
void exportarComparacoesTrocas(size_t tamanho, TipoVetor tipo);
void exportarTemposPorTipo(size_t tamanho);

#endif
