#include "testes.hpp"
#include <iostream>
#include <vector>
#include <iomanip>


using namespace std;

void testarAlgoritmo(const string& nome, void(*func)(vector<int>&, SortMetrics&), const vector<int>& original) {
    vector<int> copia = original;
    SortMetrics m;
    double tempo = medirTempo([&]() {
        func(copia, m);
    });

    cout << "=== " << nome << " ===" << endl;
    cout << fixed << setprecision(3);
    cout << "Tempo: " << tempo << " ms" << endl;
    cout << "Comparacoes: " << m.comparacoes << endl;
    cout << "Trocas: " << m.trocas << endl << endl;
}

void executarTestes(size_t tamanho, TipoVetor tipo) {
    const size_t limiteImpressao = 101;
    vector<int> original = gerarVetor(tamanho, tipo);

    if (tamanho >= 100000) {
        cout << "\n AVISO: Vetor muito grande (" << tamanho << " elementos). A execucao pode demorar.\n";
    } else if (tamanho >= 10000) {
        cout << "\n AVISO: Vetor grande. Algun algoritmos podem ser lentos. Aguarde...\n";
    }

    if (tamanho <= limiteImpressao) {
        cout << "\nVetor original:\n";
        imprimirVetor(original);
    } else {
        cout << "\n(Vetor original nao exibido: tamanho excede " << limiteImpressao << " elementos)\n";
    }

    testarAlgoritmo("Bubble Sort", bubbleSort, original);
    testarAlgoritmo("Insertion Sort", insertionSort, original);
    testarAlgoritmo("Selection Sort", selectionSort, original);
    testarAlgoritmo("Merge Sort", mergeSort, original);
    testarAlgoritmo("Quick Sort", quickSort, original);

    if (tamanho <= limiteImpressao) {
        cout << "\nVetor ordenado (Quick Sort):\n";
        vector<int> copia = original;
        SortMetrics m;
        quickSort(copia, m);
        imprimirVetor(copia);
    } else {
        cout << "\n(Vetor ordenado nao exibido: tamanho excede " << limiteImpressao << " elementos)\n";
    }
}
