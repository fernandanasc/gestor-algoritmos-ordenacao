#include <iostream>
#include <vector>
#include <sstream>
#include "vetor.hpp"
#include "teste.hpp"
#include "gestor_testes.hpp"
#include "bubble_sort.hpp"
#include "insertion_sort.hpp"
#include "selection_sort.hpp"
#include "merge_sort.hpp"
#include "quick_sort.hpp"

using namespace std;

// Função para ler vetor manual (separado por espaços)
vector<int> lerVetorManual() {
    cout << "\nDigite os numeros separados por espacos: ";
    string linha;
    cin.ignore();
    getline(cin, linha);
    
    vector<int> numeros;
    stringstream ss(linha);
    int numero;
    
    while (ss >> numero) {
        numeros.push_back(numero);
    }
    
    cout << " Vetor lido com " << numeros.size() << " elementos.\n";
    return numeros;
}

// Função para escolher tipo de vetor automático
TipoVetor escolherTipoVetor() {
    cout << "\nTipo de vetor:\n";
    cout << "1 - Aleatorio\n";
    cout << "2 - Quase Ordenado\n";
    cout << "3 - Inverso (decrescente)\n";
    cout << "Opcao: ";
    
    int opcao;
    cin >> opcao;
    
    switch (opcao) {
        case 1: return TipoVetor::ALEATORIO;
        case 2: return TipoVetor::QUASE_ORDENADO;
        case 3: return TipoVetor::INVERSO;
        default:
            cout << "Opcao invalida. Usando Aleatorio.\n";
            return TipoVetor::ALEATORIO;
    }
}

// Função para executar um algoritmo específico
void executarAlgoritmoEspecifico(Teste& teste) {
    cout << "\nEscolha o algoritmo:\n";
    cout << "1 - Bubble Sort\n";
    cout << "2 - Insertion Sort\n";
    cout << "3 - Selection Sort\n";
    cout << "4 - Merge Sort\n";
    cout << "5 - Quick Sort\n";
    cout << "Opcao: ";
    
    int opcao;
    cin >> opcao;
    
    AlgoritmoOrdenacao* algoritmo = nullptr;
    
    switch (opcao) {
        case 1: {
            static BubbleSort bubble;
            algoritmo = &bubble;
            break;
        }
        case 2: {
            static InsertionSort insertion;
            algoritmo = &insertion;
            break;
        }
        case 3: {
            static SelectionSort selection;
            algoritmo = &selection;
            break;
        }
        case 4: {
            static MergeSort merge;
            algoritmo = &merge;
            break;
        }
        case 5: {
            static QuickSort quick;
            algoritmo = &quick;
            break;
        }
        default:
            cout << "Opção inválida!\n";
            return;
    }
    
    teste.executarAlgoritmo(algoritmo);
    cout << "\n Algoritmo executado com sucesso!\n";
}

// Função para executar todos os algoritmos
void executarTodosAlgoritmos(Teste& teste) {
    static BubbleSort bubble;
    static InsertionSort insertion;
    static SelectionSort selection;
    static MergeSort merge;
    static QuickSort quick;
    
    vector<AlgoritmoOrdenacao*> algoritmos = {&bubble, &insertion, &selection, &merge, &quick};
    
    teste.executarTodosAlgoritmos(algoritmos);
}

// Função para gerenciar histórico de testes
void gerenciarHistorico(GestorTestes& gestorTestes) {
    if (!gestorTestes.temTestes()) {
        cout << "\n Nenhum teste foi executado ainda.\n";
        return;
    }
    
    while (true) {
        cout << "\n=== HISTORICO DE TESTES ===\n";
        cout << "1 - Listar todos os testes\n";
        cout << "2 - Ver detalhes de um teste\n";
        cout << "3 - Editar nome do teste\n";
        cout << "4 - Remover um teste\n";
        cout << "0 - Voltar ao menu principal\n";
        cout << "Opcao: ";
        
        int opcao;
        cin >> opcao;
        
        switch (opcao) {
            case 0:
                return;
            case 1:
                gestorTestes.exibirLista();
                break;
            case 2: {
                int id;
                cout << "Digite o ID do teste: ";
                cin >> id;
                gestorTestes.exibirDetalhes(id);
                break;
            }
            case 3: {
                int id;
                string novoNome;
                cout << "Digite o ID do teste: ";
                cin >> id;
                cout << "Novo nome: ";
                cin.ignore();
                getline(cin, novoNome);
                
                if (gestorTestes.editarTeste(id, novoNome)) {
                    cout << " Teste atualizado com sucesso!\n";
                } else {
                    cout << " Teste nao encontrado!\n";
                }
                break;
            }
            case 4: {
                int id;
                cout << "Digite o ID do teste: ";
                cin >> id;
                if (gestorTestes.removerTeste(id)) {
                    cout << " Teste removido com sucesso!\n";
                } else {
                    cout << " Teste nao encontrado!\n";
                }
                break;
            }
            default:
                cout << " Opcao invalida!\n";
        }
    }
}

int main() {
    cout << " Sistema Indicador de Algoritmos de Ordenacao\n";
    cout << "================================================\n";
    
    GestorTestes gestorTestes;
    
    while (true) {
        cout << "\n=== MENU PRINCIPAL ===\n";
        cout << "1 - Nova analise de ordenacao\n";
        cout << "2 - Consultar historico de testes\n";
        cout << "0 - Sair do programa\n";
        cout << "Opcao: ";
        
        int opcaoMenu;
        cin >> opcaoMenu;
        
        if (opcaoMenu == 0) {
            cout << "\n Encerrando programa. Obrigada!\n";
            break;
        }
        else if (opcaoMenu == 1) {
            // === ETAPA 1: ENTRADA DE DADOS ===
            cout << "\n=== ENTRADA DE DADOS ===\n";
            cout << "1 - Inserir vetor manualmente\n";
            cout << "2 - Gerar vetor automatico\n";
            cout << "Opcao: ";
            
            int opcaoEntrada;
            cin >> opcaoEntrada;
            
            Vetor vetor;
            
            if (opcaoEntrada == 1) {
                vector<int> numerosManual = lerVetorManual();
                vetor = Vetor(numerosManual);
            } 
            else if (opcaoEntrada == 2) {
                size_t tamanho;
                cout << "\nDigite o tamanho do vetor: ";
                cin >> tamanho;
                
                TipoVetor tipo = escolherTipoVetor();
                vetor = Vetor(tamanho, tipo);
            } 
            else {
                cout << " Opcao invalida!\n";
                continue;
            }
            
            // === ETAPA 2: ESCOLHA DE ALGORITMO ===
            cout << "\n=== ESCOLHA DE ALGORITMO ===\n";
            cout << "1 - Executar apenas um algoritmo\n";
            cout << "2 - Executar todos os algoritmos\n";
            cout << "Opcao: ";
            
            int opcaoAlgoritmo;
            cin >> opcaoAlgoritmo;
            
            // Criar teste com nome sequencial
            int idTeste = gestorTestes.criarTeste("temp", vetor); // Cria com nome temporário
            string nomeTeste = "Teste " + to_string(idTeste);
            
            Teste* teste = gestorTestes.buscarPorId(idTeste);
            if (teste != nullptr) {
                teste->setNome(nomeTeste); // Atualiza com o nome correto
            }
            
            if (teste == nullptr) {
                cout << " Erro ao criar teste!\n";
                continue;
            }
            
            // === ETAPA 3: EXECUÇÃO ===
            if (opcaoAlgoritmo == 1) {
                executarAlgoritmoEspecifico(*teste);
            } 
            else if (opcaoAlgoritmo == 2) {
                executarTodosAlgoritmos(*teste);
            } 
            else {
                cout << " Opcao invalida!\n";
                continue;
            }
            
            // === ETAPA 4: RESULTADO SALVO ===
            cout << "\n Analise concluida e salva no historico (ID: " << idTeste << ")!\n";
            
        }
        else if (opcaoMenu == 2) {
            gerenciarHistorico(gestorTestes);
        }
        else {
            cout << " Opcao invalida!\n";
        }
    }
    
    return 0;
}
