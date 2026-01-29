#include <iostream>   // Biblioteca para entrada e saída (cout, endl)
#include <cstdlib>    // Biblioteca que fornece rand() e srand()
#include <random>     // Biblioteca para geração de sementes aleatórias para a randomização
#include <algorithm>

using namespace std;

// ------------------------------------------------------------
// A função gerarPontos preenche um vetor de inteiros com IDs aleatórios q
// que representam possíveis pontos de pouso na superfície lunar.
//
// São usados os parâmetros:
//   pontos: ponteiro para o início do vetor de pontos de pouso
//   tamanho: quantidade de elementos do vetor
//
// Vale destacar que os valores gerados NÃO estão ordenados.
// ------------------------------------------------------------

void gerarPontos(int* pontos, int tamanho) {
    random_device rd;
    srand(rd());

    // Preenche o vetor com valores aleatórios
    for (int i = 0; i < tamanho; i++) {
        pontos[i] = rand();
    }
}

int binarySearch(const int arr[], int n, int alvo) {
    int esquerda = 0;
    int direita = n - 1;

    while(esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        if (arr[meio] == alvo) {
            return meio;
        } else if (arr[meio] < alvo) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    return -1;
}

int main() {
    // Define a quantidade de pontos de pouso disponíveis
    int tamanhoVetor = 100000;

    // Alocação dinâmica de memória para armazenar os pontos de pouso
    // Cada posição do vetor representa o ID de um ponto possível
    int* pontosDePouso = new int[tamanhoVetor];

    // Variável que armazenará o ID do ponto de pouso desejado
    int alvo;

    // Gera os pontos de pouso de forma aleatória
    gerarPontos(pontosDePouso, tamanhoVetor);

    // Seleciona aleatoriamente um ID existente no vetor
    // Isso garante que o ponto de pouso procurado realmente exista
    alvo = pontosDePouso[rand() % tamanhoVetor];

    // Exibe o ID que o sistema deverá localizar
    cout << "Buscando ponto de pouso com ID: " << alvo << endl;

    // ------------------------------------------------------------
    // A partir daqui, você deve desenvolver o algoritmo necessário
    // para localizar o ponto de pouso desejado da forma mais 
    // eficiente possível, explicando as decisões.
    // ------------------------------------------------------------

    sort(pontosDePouso, pontosDePouso + tamanhoVetor);

    int index_ordenado = binarySearch(pontosDePouso, tamanhoVetor, alvo);

    cout << "Indice no vetor ordenado: " << index_ordenado << " | Valor: " << pontosDePouso[index_ordenado] << endl;

    // Liberação da memória alocada dinamicamente
    delete[] pontosDePouso;

    return 0;
}