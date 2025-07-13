# Diagrama UML - Sistema de Algoritmos de Ordenação

## Código para Mermaid Chart

Copie e cole este código no site [mermaid.live](https://mermaid.live) para gerar o diagrama:

```mermaid
classDiagram
    class AlgoritmoOrdenacao {
        <<abstract>>
        +ordenar(vetor, metricas)*
        +getNome()
    }

    class BubbleSort {
        +ordenar(vetor, metricas)
    }

    class InsertionSort {
        +ordenar(vetor, metricas)
    }

    class SelectionSort {
        +ordenar(vetor, metricas)
    }

    class MergeSort {
        +ordenar(vetor, metricas)
    }

    class QuickSort {
        +ordenar(vetor, metricas)
    }

    class Vetor {
        -dados: vector~int~
        -tipo: string
        +criarManual()
        +criarAutomatico()
        +getDados()
        +getTamanho()
    }

    class Metricas {
        -comparacoes: int
        -trocas: int
        -tempo: double
        +incrementarComparacoes()
        +incrementarTrocas()
        +getComparacoes()
        +getTrocas()
        +getTempo()
    }

    class ResultadoTeste {
        -nomeAlgoritmo: string
        -metricas: Metricas
        +getNomeAlgoritmo()
        +getMetricas()
    }

    class Teste {
        -id: int
        -nome: string
        -vetor: Vetor
        -resultados: vector~ResultadoTeste~
        +executarAlgoritmo()
        +getMelhorResultado()
        +getRelatorio()
    }

    class GestorTestes {
        -testes: vector~Teste~
        +criarTeste()
        +editarTeste()
        +removerTeste()
        +listarTestes()
    }

    %% HERANÇA - Algoritmos herdam de AlgoritmoOrdenacao
    AlgoritmoOrdenacao <|-- BubbleSort
    AlgoritmoOrdenacao <|-- InsertionSort
    AlgoritmoOrdenacao <|-- SelectionSort
    AlgoritmoOrdenacao <|-- MergeSort
    AlgoritmoOrdenacao <|-- QuickSort

    %% RELACIONAMENTO 1:1 - Cada Teste tem exatamente 1 Vetor
    Teste ||--|| Vetor : "tem 1"

    %% RELACIONAMENTO 1:N - Um Teste tem muitos ResultadoTeste
    Teste ||--o{ ResultadoTeste : "tem muitos"

    %% RELACIONAMENTO 1:N - Um GestorTestes gerencia muitos Teste
    GestorTestes ||--o{ Teste : "gerencia muitos"

    %% RELACIONAMENTO 1:1 - Cada ResultadoTeste tem exatamente 1 Metricas
    ResultadoTeste ||--|| Metricas : "tem 1"

    %% RELACIONAMENTO N:M - Muitos Teste podem usar muitos AlgoritmoOrdenacao
    Teste }o--o{ AlgoritmoOrdenacao : "executa/usado por"
```

## Explicação dos Critérios do Trabalho

### � **Classes Implementadas (8+ classes)** ✅
1. `AlgoritmoOrdenacao` (classe abstrata)
2. `BubbleSort`
3. `InsertionSort` 
4. `SelectionSort`
5. `MergeSort`
6. `QuickSort`
7. `Vetor`
8. `Metricas`
9. `ResultadoTeste`
10. `Teste`
11. `GestorTestes`

### 🔗 **Relacionamentos Obrigatórios** ✅

#### **1:1 (Um para Um)**
- `Teste ||--|| Vetor` - Cada teste tem **exatamente 1** vetor
- `ResultadoTeste ||--|| Metricas` - Cada resultado tem **exatamente 1** métrica

#### **1:N (Um para Muitos)**
- `Teste ||--o{ ResultadoTeste` - Um teste tem **muitos** resultados
- `GestorTestes ||--o{ Teste` - Um gestor gerencia **muitos** testes

#### **N:M (Muitos para Muitos)**
- `Teste }o--o{ AlgoritmoOrdenacao` - Muitos testes podem usar muitos algoritmos

### 🏗️ **Conceitos de POO** ✅

#### **Encapsulamento**
- Atributos privados (-): `dados`, `comparacoes`, `trocas`, etc.
- Métodos públicos (+): `getDados()`, `getComparacoes()`, etc.

#### **Herança**
- `AlgoritmoOrdenacao <|-- BubbleSort` (e outros algoritmos)
- Classe pai abstrata com método virtual puro

#### **Polimorfismo**
- Método `ordenar()` implementado diferentemente em cada algoritmo
- Interface uniforme para todos os algoritmos

### 💾 **CRUD Implementado** ✅
- **Create**: `criarTeste()`
- **Read**: `listarTestes()`, `buscarPorId()`
- **Update**: `editarTeste()`
- **Delete**: `removerTeste()`

### 🎯 **Legenda dos Relacionamentos:**
- `||--||` = **1:1** (um para um)
- `||--o{` = **1:N** (um para muitos)
- `}o--o{` = **N:M** (muitos para muitos)
- `<|--` = **Herança** (é um)

### 🎯 **Como Usar:**
1. Vá para [mermaid.live](https://mermaid.live)
2. Cole o código acima
3. O diagrama será gerado automaticamente
4. Clique em "Export" para salvar como imagem

### 📝 **Para Apresentação:**
- **Explique a herança**: Todos os algoritmos seguem o mesmo padrão
- **Mostre a composição**: Como as classes se relacionam
- **Destaque a flexibilidade**: Fácil adicionar novos algoritmos

---

*Diagrama simplificado para apresentação acadêmica*  
*Desenvolvido por: Fernanda Nascimento*
