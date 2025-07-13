#include "vetor.hpp"

// Construtor padrão (vetor vazio)
Vetor::Vetor() : tamanho(0), tipo(TipoVetor::MANUAL), isManual(true) {
    inicializarDataHora();
}

// Construtor para vetor manual
Vetor::Vetor(const vector<int>& dadosUsuario) : dados(dadosUsuario), tamanho(dadosUsuario.size()), 
    tipo(TipoVetor::MANUAL), isManual(true) {
    inicializarDataHora();
    validar();
}

// Construtor para vetor automático
Vetor::Vetor(size_t tam, TipoVetor t) : tamanho(tam), tipo(t), isManual(false) {
    inicializarDataHora();
    gerar(tam, t);
}

// Gerar vetor automático
void Vetor::gerar(size_t tam, TipoVetor t) {
    validarTamanho(tam);
    
    tamanho = tam;
    tipo = t;
    isManual = false;
    
    switch (t) {
        case TipoVetor::ALEATORIO:
            gerarVetorAleatorio(tam);
            break;
        case TipoVetor::QUASE_ORDENADO:
            gerarVetorQuaseOrdenado(tam);
            break;
        case TipoVetor::INVERSO:
            gerarVetorInverso(tam);
            break;
        case TipoVetor::MANUAL:
            throw ExcecaoVetor("Use setDadosManual() para vetores manuais");
    }
}

// Definir dados manualmente
void Vetor::setDadosManual(const vector<int>& dadosUsuario) {
    dados = dadosUsuario;
    tamanho = dadosUsuario.size();
    tipo = TipoVetor::MANUAL;
    isManual = true;
    validar();
}

// Getters
vector<int> Vetor::getDados() const {
    return dados;
}

vector<int> Vetor::getCopia() const {
    return vector<int>(dados);
}

size_t Vetor::getTamanho() const {
    return tamanho;
}

TipoVetor Vetor::getTipo() const {
    return tipo;
}

string Vetor::getTipoString() const {
    return tipoParaString(tipo);
}

bool Vetor::ehManual() const {
    return isManual;
}

string Vetor::getDataHoraCriacao() const {
    return dataHoraCriacao;
}

// Métodos de utilidade
void Vetor::imprimir() const {
    if (estaVazio()) {
        cout << "Vetor vazio" << endl;
        return;
    }
    
    cout << "Vetor " << getTipoString() << " (tamanho: " << tamanho << "): ";
    for (size_t i = 0; i < dados.size() && i < 20; ++i) { // Mostra apenas primeiros 20 elementos
        cout << dados[i] << " ";
    }
    if (dados.size() > 20) {
        cout << "... (+" << (dados.size() - 20) << " elementos)";
    }
    cout << endl;
}

void Vetor::validar() {
    if (dados.size() != tamanho) {
        throw ExcecaoVetor("Tamanho inconsistente: dados.size() != tamanho");
    }
}

bool Vetor::estaVazio() const {
    return dados.empty() || tamanho == 0;
}

// Métodos estáticos
string Vetor::tipoParaString(TipoVetor tipo) {
    switch (tipo) {
        case TipoVetor::ALEATORIO: return "Aleatório";
        case TipoVetor::QUASE_ORDENADO: return "Quase Ordenado";
        case TipoVetor::INVERSO: return "Inverso";
        case TipoVetor::MANUAL: return "Manual";
        default: return "Desconhecido";
    }
}

TipoVetor Vetor::stringParaTipo(const string& str) {
    if (str == "Aleatório" || str == "ALEATORIO") return TipoVetor::ALEATORIO;
    if (str == "Quase Ordenado" || str == "QUASE_ORDENADO") return TipoVetor::QUASE_ORDENADO;
    if (str == "Inverso" || str == "INVERSO") return TipoVetor::INVERSO;
    if (str == "Manual" || str == "MANUAL") return TipoVetor::MANUAL;
    throw ExcecaoVetor("Tipo de vetor desconhecido: " + str);
}

// Métodos privados auxiliares
void Vetor::inicializarDataHora() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_mday << "/"
       << setw(2) << (1 + ltm->tm_mon) << "/"
       << (1900 + ltm->tm_year) << " "
       << setw(2) << ltm->tm_hour << ":"
       << setw(2) << ltm->tm_min << ":"
       << setw(2) << ltm->tm_sec;
    
    dataHoraCriacao = ss.str();
}

void Vetor::validarTamanho(size_t tam) {
    if (tam == 0) {
        throw ExcecaoVetor("Tamanho do vetor não pode ser zero");
    }
    if (tam > 1000000) { // Limite razoável
        throw ExcecaoVetor("Tamanho do vetor muito grande (máximo: 1.000.000)");
    }
}

void Vetor::gerarVetorAleatorio(size_t tam) {
    dados.resize(tam);
    srand(time(nullptr));
    
    for (size_t i = 0; i < tam; ++i) {
        dados[i] = rand() % 10000; // Números de 0 a 9999
    }
}

void Vetor::gerarVetorQuaseOrdenado(size_t tam) {
    // Primeiro gera aleatório
    gerarVetorAleatorio(tam);
    
    // Ordena
    sort(dados.begin(), dados.end());
    
    // Faz algumas trocas aleatórias (5% dos elementos)
    size_t numTrocas = max(static_cast<size_t>(1), tam / 20);
    for (size_t i = 0; i < numTrocas; ++i) {
        size_t pos1 = rand() % tam;
        size_t pos2 = rand() % tam;
        swap(dados[pos1], dados[pos2]);
    }
}

void Vetor::gerarVetorInverso(size_t tam) {
    // Primeiro gera aleatório
    gerarVetorAleatorio(tam);
    
    // Ordena em ordem decrescente
    sort(dados.begin(), dados.end(), greater<int>());
}