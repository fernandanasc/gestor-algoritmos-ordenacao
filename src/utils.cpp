#include "utils.hpp"
#include "bubble_sort.hpp"
#include "insertion_sort.hpp"
#include "selection_sort.hpp"
#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include <algorithm>

using namespace std;

vector<int> gerarVetor(size_t tamanho, TipoVetor tipo) {
    vector<int> v(tamanho);

    srand(time(nullptr));
    for (size_t i = 0; i < tamanho; ++i)
        v[i] = rand() % 10000;

    if (tipo == TipoVetor::QUASE_ORDENADO) {
        sort(v.begin(), v.end());
        for (size_t i = 0; i < tamanho / 20; ++i)
            swap(v[rand() % tamanho], v[rand() % tamanho]);
    }
    else if (tipo == TipoVetor::INVERSO) {
        sort(v.begin(), v.end(), greater<int>());
    }

    return v;
}

void imprimirVetor(const vector<int>& v) {
    for (auto val : v)
        cout << val << " ";
    cout << endl;
}

bool desejaContinuar() {
    char repetir;
    while (true) {
        cout << "\nDeseja realizar outro teste? (s/n): ";
        cin >> repetir;

        if (repetir == 's' || repetir == 'S') return true;
        if (repetir == 'n' || repetir == 'N') return false;

        cout << "Entrada invalida. Por favor, digite 's' para sim ou 'n' para nao.\n";
    }
}

string tipoVetorParaString(TipoVetor tipo) {
    switch (tipo) {
        case TipoVetor::ALEATORIO: return "Aleatorio";
        case TipoVetor::QUASE_ORDENADO: return "Quase_Ordenado";
        case TipoVetor::INVERSO: return "Inverso";
        default: return "Desconhecido";
    }
}

string formatarNumeroCSV(double numero) {
    string resultado = to_string(numero);
    // Substitui ponto por vírgula para formato brasileiro
    size_t pos = resultado.find('.');
    if (pos != string::npos) {
        resultado[pos] = ',';
    }
    // Remove zeros desnecessários no final
    if (resultado.find(',') != string::npos) {
        resultado.erase(resultado.find_last_not_of('0') + 1, string::npos);
        resultado.erase(resultado.find_last_not_of(',') + 1, string::npos);
    }
    return resultado;
}

TestData testarAlgoritmoParaCSV(const string& nome, void(*func)(vector<int>&, SortMetrics&), const vector<int>& original, TipoVetor tipo) {
    vector<int> copia = original;
    SortMetrics m;
    double tempo = medirTempo([&]() {
        func(copia, m);
    });

    TestData data;
    data.algoritmo = nome;
    data.tipoVetor = tipoVetorParaString(tipo);
    data.tamanho = original.size();
    data.tempo = tempo;
    data.comparacoes = m.comparacoes;
    data.trocas = m.trocas;
    
    return data;
}

void exportarDadosCompletos() {
    vector<size_t> tamanhos = {100, 500, 1000, 2000, 5000, 10000};
    vector<TipoVetor> tipos = {TipoVetor::ALEATORIO, TipoVetor::QUASE_ORDENADO, TipoVetor::INVERSO};
    vector<TestData> dados;

    cout << "\n=== COLETANDO DADOS PARA GRAFICO DE LINHAS ===\n";
    cout << "Testando todos os algoritmos com diferentes tamanhos e tipos de vetor...\n";
    
    for (size_t tamanho : tamanhos) {
        for (TipoVetor tipo : tipos) {
            vector<int> vetor = gerarVetor(tamanho, tipo);
            
            dados.push_back(testarAlgoritmoParaCSV("Bubble_Sort", bubbleSort, vetor, tipo));
            dados.push_back(testarAlgoritmoParaCSV("Insertion_Sort", insertionSort, vetor, tipo));
            dados.push_back(testarAlgoritmoParaCSV("Selection_Sort", selectionSort, vetor, tipo));
            dados.push_back(testarAlgoritmoParaCSV("Merge_Sort", mergeSort, vetor, tipo));
            dados.push_back(testarAlgoritmoParaCSV("Quick_Sort", quickSort, vetor, tipo));
        }
    }

    cout << "\n\n=== SALVANDO ARQUIVO CSV ===\n";
    // Exportar para CSV - Gráfico de linhas (tempo x tamanho)
    ofstream arquivo1("data/tempo_por_tamanho.csv");
    arquivo1 << "Tamanho;Tempo_ms;Tipo_Vetor;Algoritmo\n";
    for (const auto& d : dados) {
        arquivo1 << d.tamanho << ";" << formatarNumeroCSV(d.tempo) << ";" << d.tipoVetor << ";" << d.algoritmo << "\n";
    }
    arquivo1.close();

    cout << "Arquivo 'data/tempo_por_tamanho.csv' criado com sucesso!\n";
}

void exportarComparacoesTrocas(size_t tamanho, TipoVetor tipo) {
    cout << "\n=== COLETANDO DADOS DE COMPARACOES E TROCAS ===\n";
    cout << "Tamanho: " << tamanho << " elementos\n";
    cout << "Tipo: " << tipoVetorParaString(tipo) << "\n\n";
    
    vector<int> vetor = gerarVetor(tamanho, tipo);
    vector<TestData> dados;

    cout << "Testando algoritmos...\n";
    dados.push_back(testarAlgoritmoParaCSV("Bubble_Sort", bubbleSort, vetor, tipo));
    dados.push_back(testarAlgoritmoParaCSV("Insertion_Sort", insertionSort, vetor, tipo));
    dados.push_back(testarAlgoritmoParaCSV("Selection_Sort", selectionSort, vetor, tipo));
    dados.push_back(testarAlgoritmoParaCSV("Merge_Sort", mergeSort, vetor, tipo));
    dados.push_back(testarAlgoritmoParaCSV("Quick_Sort", quickSort, vetor, tipo));

    // Exportar para CSV - Gráfico de barras (comparações e trocas)
    string nomeArquivo = "data/comparacoes_trocas_" + to_string(tamanho) + "_" + tipoVetorParaString(tipo) + ".csv";
    ofstream arquivo(nomeArquivo);
    arquivo << "Algoritmo;Comparacoes;Trocas\n";
    for (const auto& d : dados) {
        arquivo << d.algoritmo << ";" << d.comparacoes << ";" << d.trocas << "\n";
    }
    arquivo.close();

    cout << "\n Arquivo '" << nomeArquivo << "' criado com sucesso!\n";
}

void exportarTemposPorTipo(size_t tamanho) {
    cout << "\n=== COLETANDO DADOS DE TEMPO POR TIPO DE VETOR ===\n";
    cout << "Tamanho: " << tamanho << " elementos\n";
    cout << "Comparando os 3 tipos de vetor para todos os algoritmos...\n\n";
    
    vector<TipoVetor> tipos = {TipoVetor::ALEATORIO, TipoVetor::QUASE_ORDENADO, TipoVetor::INVERSO};
    vector<TestData> dados;

    for (TipoVetor tipo : tipos) {
        vector<int> vetor = gerarVetor(tamanho, tipo);
        
        dados.push_back(testarAlgoritmoParaCSV("Bubble_Sort", bubbleSort, vetor, tipo));
        dados.push_back(testarAlgoritmoParaCSV("Insertion_Sort", insertionSort, vetor, tipo));
        dados.push_back(testarAlgoritmoParaCSV("Selection_Sort", selectionSort, vetor, tipo));
        dados.push_back(testarAlgoritmoParaCSV("Merge_Sort", mergeSort, vetor, tipo));
        dados.push_back(testarAlgoritmoParaCSV("Quick_Sort", quickSort, vetor, tipo));
    }

    // Exportar para CSV - Gráfico de barras (tempo por tipo de vetor)
    string nomeArquivo = "data/tempo_por_tipo_" + to_string(tamanho) + ".csv";
    ofstream arquivo(nomeArquivo);
    arquivo << "Algoritmo;Tipo_Vetor;Tempo_ms\n";
    for (const auto& d : dados) {
        arquivo << d.algoritmo << ";" << d.tipoVetor << ";" << formatarNumeroCSV(d.tempo) << "\n";
    }
    arquivo.close();

    cout << "\n Arquivo '" << nomeArquivo << "' criado com sucesso!\n";
}

