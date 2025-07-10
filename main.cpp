#include <iostream>
#include <vector>
#include "utils.hpp"
#include "bubble_sort.hpp"
#include "insertion_sort.hpp"
#include "selection_sort.hpp"
#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include "testes.hpp"

using namespace std;


int main() {
    
    while (true) {
        cout << "\n============== ANALISE DE ALGORITMOS DE ORDENACAO ==============\n";
        cout << "1 - Executar teste individual (exibir resultados na tela)\n";
        cout << "2 - Gerar CSV: Tempo x Tamanho (para grafico de linhas)\n";
        cout << "3 - Gerar CSV: Comparacoes e Trocas (para grafico de barras)\n";
        cout << "4 - Gerar CSV: Tempo por Tipo de Vetor (para grafico de barras)\n";
        cout << "0 - Sair do programa\n";
        cout << "================================================================\n";
        cout << "Escolha uma opcao: ";
        
        int opcao;
        cin >> opcao;
        
        if (opcao == 0) {
            cout << "\nEncerrando programa. Obrigado por usar!\n";
            return 0;
        }
        else if (opcao == 1) {
            cout << "\n--- TESTE INDIVIDUAL ---\n";
            size_t tamanho;
            int tipoEscolhido;

            cout << "Digite o tamanho do vetor: ";
            cin >> tamanho;

            cout << "\nTipo de vetor:\n";
            cout << "1 - Aleatorio\n";
            cout << "2 - Quase Ordenado\n";
            cout << "3 - Inverso (decrescente)\n";
            cout << "Opcao: ";
            cin >> tipoEscolhido;

            TipoVetor tipo;
            switch (tipoEscolhido) {
                case 1: tipo = TipoVetor::ALEATORIO; 
                break;
                case 2: tipo = TipoVetor::QUASE_ORDENADO;
                break;
                case 3: tipo = TipoVetor::INVERSO; 
                break;
                default:
                    cout << "Opcao invalida. Usando ALEATORIO como padrao.\n";
                    tipo = TipoVetor::ALEATORIO;
            }

            executarTestes(tamanho, tipo);
        }
        else if (opcao == 2) {
            cout << "\n--- GERACAO DE DADOS PARA GRAFICO DE LINHAS ---\n";
            cout << "Vai testar todos os algoritmos com:\n";
            cout << "- Tamanhos: 100, 500, 1.000, 2.000, 5.000, 10.000 \n";
            cout << "- Tipos: Aleatorio, Quase Ordenado, Inverso\n";
            cout << "- Arquivo gerado: data/tempo_por_tamanho.csv\n";
            cout << "\nPode demorar um pouco. Quer continuar? (s/n): ";
            
            char confirma;
            cin >> confirma;
            
            if (confirma == 's' || confirma == 'S') {
                exportarDadosCompletos();
            } else {
                cout << "Operacao cancelada.\n";
            }
        }
        else if (opcao == 3) {
            cout << "\n--- GERACAO DE DADOS PARA GRAFICO DE BARRAS (Comparacoes/Trocas) ---\n";
            size_t tamanho;
            int tipoEscolhido;

            cout << "Digite o tamanho do vetor para analise: ";
            cin >> tamanho;

            cout << "\nTipo de vetor:\n";
            cout << "1 - Aleatorio\n";
            cout << "2 - Quase Ordenado\n";
            cout << "3 - Inverso (decrescente)\n";
            cout << "Opcao: ";
            cin >> tipoEscolhido;

            TipoVetor tipo;
            switch (tipoEscolhido) {
                case 1: tipo = TipoVetor::ALEATORIO; 
                break;
                case 2: tipo = TipoVetor::QUASE_ORDENADO;
                break;
                case 3: tipo = TipoVetor::INVERSO; 
                break;
                default:
                    cout << "Opcao invalida. Usando ALEATORIO como padrao.\n";
                    tipo = TipoVetor::ALEATORIO;
            }

            exportarComparacoesTrocas(tamanho, tipo);
        }
        else if (opcao == 4) {
            cout << "\n--- GERACAO DE DADOS PARA GRAFICO DE BARRAS (Tempo por Tipo) ---\n";
            size_t tamanho;
            cout << "Digite o tamanho do vetor para comparacao entre tipos: ";
            cin >> tamanho;
            
            cout << "\nVai gerar dados de tempo para todos os algoritmos\n";
            cout << "comparando os 3 tipos de vetor (Aleatorio, Quase Ordenado, Inverso)\n";
            cout << "Arquivo gerado: data/tempo_por_tipo_" << tamanho << ".csv\n";
            
            exportarTemposPorTipo(tamanho);
        }
        else {
            cout << "\n*** Opcao invalida! Escolha uma opcao de 0 a 4. ***\n";
        }
    }
}
