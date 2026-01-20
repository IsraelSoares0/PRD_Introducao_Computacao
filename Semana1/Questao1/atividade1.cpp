#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Bairro {
    int index;
    string nome;
    int viabilidade;
    int fluxo[3];
};

void obter_bairros_viaveis(Bairro bairros[], int& size) {
    for (int i = 0; i < size; i++) {
        // Verifica todos os bairros com viabilidade < 70 e "retira" eles do array
        if (bairros[i].viabilidade < 70) {
            for (int j = i; j < size - 1; ++j) {
                bairros[j] = bairros[j + 1];
            }
            --size;     // Reducao do tamanho
            --i;        // Reavaliar posicao atual
        }
    }
}

int main() {
    // Lista de bairros, viabilidade e fluxo
    int size = 20;

    Bairro bairros[20] = {
        {0,  "Abanotubani",   .viabilidade = 82,   .fluxo = {4, 2, 9}},
        {1,  "Lisi",          .viabilidade = 55,   .fluxo = {3, 4, 7}},
        {2,  "Digomi",        .viabilidade = 74,   .fluxo = {0, 4, 9}},
        {3,  "Saburtalo",     .viabilidade = 69,   .fluxo = {4, 2, 10}},
        {4,  "Vake",          .viabilidade = 90,   .fluxo = {3, 7, 11}},
        {5,  "Nutsubidze",    .viabilidade = 73,   .fluxo = {4, 7, 16}},
        {6,  "Ortachala",     .viabilidade = 88,   .fluxo = {7, 4, 8}},
        {7,  "Mtatsminda",    .viabilidade = 77,   .fluxo = {4, 6, 11}},
        {8,  "Isani",         .viabilidade = 62,   .fluxo = {6, 9, 14}},
        {9,  "Gldani",        .viabilidade = 85,   .fluxo = {4, 2, 13}},
        {10, "Marjanishvili", .viabilidade = 71,   .fluxo = {11, 3, 16}},
        {11, "Rustaveli",     .viabilidade = 92,   .fluxo = {4, 7, 15}},
        {12, "Avlabari",      .viabilidade = 68,   .fluxo = {8, 11, 17}},
        {13, "Nadzaladevi",   .viabilidade = 74,   .fluxo = {15, 9, 2}},
        {14, "Samgori",       .viabilidade = 58,   .fluxo = {17, 8, 12}},
        {15, "Didube",        .viabilidade = 80,   .fluxo = {11, 13, 2}},
        {16, "Chugureti",     .viabilidade = 76,   .fluxo = {10, 5, 18}},
        {17, "Varketili",     .viabilidade = 65,   .fluxo = {14, 8, 12}},
        {18, "Sanzona",       .viabilidade = 79,   .fluxo = {16, 19, 13}},
        {19, "Kiketi",        .viabilidade = 83,   .fluxo = {17, 11, 18}}
    };

    // Matriz de distâncias | 0 representa caminho inválido
    int dist[20][20] = {
        /*0 */ { 0, 0, 4, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 9, 0,10, 0, 0, 0, 0 },
        /*1 */ { 0, 0, 0, 5, 7, 0, 0, 9, 0, 0,11, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        /*2 */ { 4, 0, 0, 3, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0 },
        /*3 */ { 0, 5, 3, 0, 4, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        /*4 */ { 0, 7, 0, 4, 0, 3, 0, 6, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0 },
        /*5 */ { 0, 0, 0, 0, 3, 0, 0, 7, 0, 0, 9, 0, 0, 0, 0, 0, 8, 0, 0, 0 },
        /*6 */ { 0, 0, 0, 0, 0, 0, 0, 5, 9, 0, 0,10, 8, 0, 0, 0, 0, 0, 0, 0 },
        /*7 */ { 0, 9, 0, 0, 6, 7, 5, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0 },
        /*8 */ { 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 4, 0, 6, 0, 0, 4, 0, 0 },
        /*9 */ { 7, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 8, 0 },
        /*10*/ { 0,11, 0, 6, 0, 9, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 6, 0, 0, 0 },
        /*11*/ { 0, 0, 0, 0, 4, 0,10, 3, 0, 0, 3, 0, 0, 0, 0, 5, 7, 0, 0,11 },
        /*12*/ { 0, 0, 0, 0, 0, 0, 8, 0, 4, 0, 0, 0, 0, 0, 5, 0, 0, 6, 0, 0 },
        /*13*/ { 9, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 7, 0, 0, 9, 0 },
        /*14*/ { 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 5, 0, 0, 0, 0, 3, 0,10 },
        /*15*/ {10, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 7, 0, 0, 0, 0, 0, 0 },
        /*16*/ { 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0, 0, 5, 0 },
        /*17*/ { 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 6, 0, 3, 0, 0, 0, 0, 8 },
        /*18*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 9, 0, 0, 5, 0, 0, 7 },
        /*19*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0,10, 0, 0, 8, 7, 0 }
    };

    obter_bairros_viaveis(bairros, size);

    

    return 0;
}