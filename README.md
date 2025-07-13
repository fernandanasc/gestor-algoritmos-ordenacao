#  Sistema Analisador de Algoritmos de Ordenação

Um sistema completo em C++ para análise e comparação de algoritmos de ordenação, desenvolvido com foco em **Programação Orientada a Objetos** e **boas práticas de desenvolvimento**.

## 📋 Sobre o Projeto

Este projeto implementa um sistema interativo que permite:
- **Criar vetores** (manual ou automático)
- **Executar algoritmos de ordenação** (individual ou comparativo)
- **Analisar resultados** com métricas detalhadas
- **Gerenciar histórico** de testes (CRUD completo)
- **Identificar o algoritmo mais eficiente** para diferentes cenários

### 🎯 Algoritmos Implementados

| Algoritmo | Complexidade (Médio) | Complexidade (Pior) | Estável |
|-----------|---------------------|---------------------|---------|
| **Bubble Sort** | O(n²) | O(n²) | ✅ |
| **Insertion Sort** | O(n²) | O(n²) | ✅ |
| **Selection Sort** | O(n²) | O(n²) | ❌ |
| **Merge Sort** | O(n log n) | O(n log n) | ✅ |
| **Quick Sort** | O(n log n) | O(n²) | ❌ |

## 🏗️ Arquitetura do Sistema

```
📁 Projeto/
├── 📁 include/           # Cabeçalhos (.hpp)
│   ├── algoritmo_ordenacao.hpp  # Classe base abstrata
│   ├── bubble_sort.hpp          # Implementação Bubble Sort
│   ├── insertion_sort.hpp       # Implementação Insertion Sort
│   ├── selection_sort.hpp       # Implementação Selection Sort
│   ├── merge_sort.hpp           # Implementação Merge Sort
│   ├── quick_sort.hpp           # Implementação Quick Sort
│   ├── metricas.hpp             # Classe para métricas de desempenho
│   ├── vetor.hpp                # Classe para manipulação de vetores
│   ├── resultado_teste.hpp      # Classe para resultados individuais
│   ├── teste.hpp                # Classe para gerenciar execuções
│   └── gestor_testes.hpp        # Classe para CRUD de testes
├── 📁 src/              # Implementações (.cpp)
├── � docs/             # Documentação técnica
│   └── diagrama.md      # Diagrama UML (Mermaid)
├── �📄 main.cpp          # Interface principal
├── 📄 Makefile         # Sistema de build
└── 📄 README.md        # Este arquivo
```

## 🔧 Tecnologias e Conceitos

### **Programação Orientada a Objetos**
- ✅ **Encapsulamento**: Dados privados com interfaces públicas controladas
- ✅ **Herança**: Classe base `AlgoritmoOrdenacao` com implementações específicas
- ✅ **Polimorfismo**: Método virtual `ordenar()` com comportamentos diferentes
- ✅ **Abstração**: Classes abstratas e interfaces bem definidas

##  Como Executar

### **Pré-requisitos**
- Compilador C++17 ou superior (GCC, Clang, MSVC)
- Make (opcional, mas recomendado)

### **Compilação**

#### Usando Make (Recomendado)
```bash
# Compilar o projeto
make

# Limpar arquivos objeto
make clean
```

#### Compilação Manual
```bash
g++ -std=c++17 -Wall -Ofast -Iinclude -o main.exe main.cpp src/*.cpp
```

### **Execução**
```bash
./main.exe        # Linux/Mac
main.exe          # Windows
```

##  Como Usar

### **1. Criação de Vetores**
```
=== ENTRADA DE DADOS ===
1 - Inserir vetor manualmente
2 - Gerar vetor automático
```

**Tipos de vetores automáticos:**
- 🎲 **Aleatório**: Elementos embaralhados
- 📊 **Quase Ordenado**: 95% ordenado com algumas trocas
- 📉 **Inverso**: Ordenado de forma decrescente

### **2. Execução de Algoritmos**
```
=== ESCOLHA DE ALGORITMO ===
1 - Executar apenas um algoritmo
2 - Executar todos os algoritmos
```

### **3. Análise de Resultados**
O sistema exibe métricas detalhadas:
- ⏱️ **Tempo de execução** (milissegundos)
- 🔄 **Número de comparações**
- 🔀 **Número de trocas**
- 🏆 **Ranking de eficiência**

### **4. Gerenciamento de Histórico**
```
=== HISTÓRICO DE TESTES ===
1 - Listar todos os testes
2 - Ver detalhes de um teste
3 - Editar nome do teste
4 - Remover um teste
```

## 📊 Exemplo de Saída

```
=== EXECUTANDO TESTE: Teste 1 ===
Tipo de vetor: Aleatorio
Tamanho: 1000 elementos

=== Bubble Sort ===
Tempo: 3.247 ms
Comparações: 499500
Trocas: 249750

=== Quick Sort ===
Tempo: 0.156 ms
Comparações: 10342
Trocas: 2847

🏆 MELHOR ALGORITMO: Quick Sort (0.156 ms)
```

## 🎯 Critérios de Avaliação

O sistema determina o **melhor algoritmo** baseado em:

1. **Tempo de execução** (prioridade principal)
2. **Número de trocas** (operações mais custosas)
3. **Número de comparações** (critério de desempate)

## ️ Estrutura das Classes

### **Classe Base: AlgoritmoOrdenacao**
```cpp
class AlgoritmoOrdenacao {
public:
    virtual void ordenar(vector<int>& vetor, Metricas& metricas) = 0;
    string getNome() const;
};
```

### **Classe de Métricas**
```cpp
class Metricas {
private:
    size_t comparacoes, trocas;
    double tempoExecucao;
public:
    void incrementarComparacoes();
    void incrementarTrocas();
    // ... getters
};
```

## 📈 Funcionalidades Principais

- 🔧 **CRUD Completo**: Criar, consultar, editar e remover testes
- 📊 **Métricas Detalhadas**: Tempo, comparações e trocas
- 🏆 **Ranking Automático**: Identifica o algoritmo mais eficiente
- 💾 **Histórico Persistente**: Mantém registro de todas as execuções
- 🎛️ **Interface Intuitiva**: Menu interativo e feedback claro

## 🤝 Sobre o Desenvolvimento

Este projeto foi desenvolvido como **atividade final da disciplina de Linguagem de Programação 1**, demonstrando a aplicação prática de conceitos fundamentais de **Programação Orientada a Objetos** em C++.

## 👨‍💻 Autor

**Fernanda Nascimento**  
Projeto desenvolvido para demonstrar domínio dos conceitos de Programação Orientada a Objetos e estruturas de dados.

---

⭐ **Projeto acadêmico de Algoritmos de Ordenação** ⭐