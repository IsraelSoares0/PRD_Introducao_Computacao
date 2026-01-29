#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <tuple>
#include <algorithm>

using namespace std;

struct Bairro {
    int index;
    string nome;
    int viabilidade;
    int fluxo[3];
};

struct Linha {
    vector<tuple<int, int>> percurso; // (indice array, indice original)
    int tamanho;
    int soma_viabilidade = 0;
    double media_viabilidade = 0.0;
    int demanda_atendida;
    int custo = 0;

    double indice_construcao = 0.0;
    bool aprovada = false;
};

Linha construir_linha(const vector<int>& caminho, Bairro bairros[], int dist[20][20]);
void obter_bairros_viaveis(Bairro bairros[], int* size);
void dfs_caminhos(Bairro bairros[], int size, int dist[20][20], int atual, vector<int>& caminho_atual, vector<Linha>& linhas);
vector<Linha> encontrar_linhas_metro(Bairro bairros[], int size, int dist[20][20]);
Linha construir_linha(const vector<int>& caminho, Bairro bairros[], int dist[20][20]);

void obter_bairros_viaveis(Bairro bairros[], int* size) {
    for (int i = 0; i < (*size); i++) {
        // Verifica todos os bairros com viabilidade < 70 e "retira" eles do array
        if (bairros[i].viabilidade < 70) {
            for (int j = i; j < (*size) - 1; ++j) {
                bairros[j] = bairros[j + 1];
            }
            --(*size);     // Reducao do tamanho
            --i;        // Reavaliar posicao atual
        }
    }
}

void dfs_caminhos(Bairro bairros[], int size, int dist[20][20], int atual, vector<int>& caminho_atual, vector<Linha>& linhas) {
    // Se caminho pelo menos 3 bairros, armazena
    if (caminho_atual.size() >= 3) {
        linhas.push_back(construir_linha(caminho_atual, bairros, dist));
    }

    // Tenta expandir
    for (int j = 0; j < 3; j++) {
        int prox_index_original = bairros[atual].fluxo[j];
        int d = dist[bairros[atual].index][prox_index_original];

        if (d <= 0 || d > 10) continue;

        // Encontrar o indice do proximo bairro viavel
        int prox = -1;
        for (int k = 0; k < size; k++) {
            if (bairros[k].index == prox_index_original) {
                prox = k;
                break;
            }
        }
        if (prox == -1) continue;

        // Evita Ciclos
        if (find(caminho_atual.begin(), caminho_atual.end(), prox) != caminho_atual.end()) continue;

        // Backtracking
        caminho_atual.push_back(prox);
        dfs_caminhos(bairros, size, dist, prox, caminho_atual, linhas);
        caminho_atual.pop_back();
    }
}

vector<Linha> encontrar_linhas_metro(Bairro bairros[], int size, int dist[20][20]) {
    vector<Linha> linhas;

    for (int i = 0; i < size; i++) {
        vector<int> caminho_atual;
        caminho_atual.push_back(i);
        dfs_caminhos(bairros, size, dist, i, caminho_atual, linhas);
    }

    return linhas;
}

Linha construir_linha(const vector<int>& caminho, Bairro bairros[], int dist[20][20]) {
    Linha linha{};

    linha.tamanho = caminho.size();
    
    // Preenche percurso e soma viabilidades
    for (int idx : caminho) {
        linha.percurso.emplace_back(idx, bairros[idx].index);
        linha.soma_viabilidade += bairros[idx].viabilidade;
    }

    linha.media_viabilidade = static_cast<double>(linha.soma_viabilidade) / linha.tamanho;

    // Demanda atendida e custo
    for (int i = 0; i < caminho.size() - 1; i++) {
        int A = caminho[i];
        int B = caminho[i + 1];

        int indexA = bairros[A].index;
        int indexB = bairros[B].index;

        int d = dist[indexA][indexB];
        if (d > 0) linha.custo += d;

        for (int f = 0; f < 3; f++) {
            if (bairros[A].fluxo[f] == indexB) {
                linha.demanda_atendida++;
                break;
            }
        }
    }

    linha.indice_construcao = (linha.custo > 0) ? linha.demanda_atendida * linha.media_viabilidade / linha.custo : 0.0;

    if (linha.indice_construcao >= 10) linha.aprovada = true;

    return linha;
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

    vector<tuple<int, int, int>> caminhos;

    obter_bairros_viaveis(bairros, &size);

    auto linhas = encontrar_linhas_metro(bairros, size, dist);

    sort(linhas.begin(), linhas.end(), [](const Linha& a, const Linha& b) {
        return a.indice_construcao > b.indice_construcao;
    });

    cout << "Bairros Viáveis: " << size << endl << endl;

    for (int i = 0; i < size; i++) {
        cout << "ID: " << bairros[i].index << " | Nome: " << bairros[i].nome << " | Viabilidade: " << bairros[i].viabilidade << endl;
    }
    cout << endl;

    cout << "20 Conexões Recomendadas: " << endl << endl;

    for (int i = 0; i < 20; i++) {
        const Linha& L = linhas[i];

        cout << "Linha " << i + 1 << ":" << endl;

        cout << "  Percurso: ";
        for (const auto& p : L.percurso) {
            int idx_array    = get<0>(p);
            int idx_original = get<1>(p);
            cout << bairros[idx_array].nome
                << "(" << idx_original << ") ";
        }
        cout << endl;

        cout << "  Tamanho da linha: " << L.tamanho << endl;
        cout << "  Soma das viabilidades: " << L.soma_viabilidade << endl;
        cout << "  Media de viabilidade: " << L.media_viabilidade << endl;
        cout << "  Demanda atendida: " << L.demanda_atendida << endl;
        cout << "  Custo da linha: " << L.custo << endl;
        cout << "  Indice da linha: " << L.indice_construcao << endl;

        cout << "-------------------------------------" << endl;
    }

    cout << endl << "Total de linhas encontradas: " << linhas.size() << endl << endl;

    for (int i = 0; i < linhas.size(); i++) {
        const Linha& L = linhas[i];

        cout << "Linha " << i + 1 << ":" << endl;

        cout << "  Percurso: ";
        for (const auto& p : L.percurso) {
            int idx_array    = get<0>(p);
            int idx_original = get<1>(p);
            cout << bairros[idx_array].nome
                << "(" << idx_original << ") ";
        }
        cout << endl;

        cout << "  Tamanho da linha: " << L.tamanho << endl;
        cout << "  Soma das viabilidades: " << L.soma_viabilidade << endl;
        cout << "  Media de viabilidade: " << L.media_viabilidade << endl;
        cout << "  Demanda atendida: " << L.demanda_atendida << endl;
        cout << "  Custo da linha: " << L.custo << endl;
        cout << "  Indice da linha: " << L.indice_construcao << endl;

        cout << "-------------------------------------" << endl;
    }

    cout << "Linhas aprovadas: " << endl << endl;
    int aprovadas = 0;

    for (int i = 0; i < linhas.size(); i++) {
        const Linha& L = linhas[i];

        if (L.aprovada == false) {
            continue;
        } else {
            aprovadas++;
        }

        cout << "Linha " << i + 1 << ":" << endl;

        cout << "  Percurso: ";
        for (const auto& p : L.percurso) {
            int idx_array    = get<0>(p);
            int idx_original = get<1>(p);
            cout << bairros[idx_array].nome
                << "(" << idx_original << ") ";
        }
        cout << endl;

        cout << "  Tamanho da linha: " << L.tamanho << endl;
        cout << "  Soma das viabilidades: " << L.soma_viabilidade << endl;
        cout << "  Media de viabilidade: " << L.media_viabilidade << endl;
        cout << "  Demanda atendida: " << L.demanda_atendida << endl;
        cout << "  Custo da linha: " << L.custo << endl;
        cout << "  Indice da linha: " << L.indice_construcao << endl;

        cout << "-------------------------------------" << endl;
    }

    cout << endl << "Métricas gerais" << endl << endl;

    cout << "Porcentagem de Bairros aprovados: " << (static_cast<double>(size) / 20) * 100 << "%" << endl;
    cout << "Quantidade de linhas encontradas: " << linhas.size() << endl;
    cout << "Porcentagem de linhas aprovadas: " << (static_cast<double>(aprovadas) / linhas.size()) * 100 << "%";

    cout << endl << "Melhor Linha: " << endl << endl;

    cout << "-------------------------------------" << endl << endl;

    cout << "Linha " << 0 << ":" << endl;

    cout << "  Percurso: ";
    for (const auto& p : linhas[0].percurso) {
        int idx_array    = get<0>(p);
        int idx_original = get<1>(p);
        cout << bairros[idx_array].nome << "(" << idx_original << ") ";
    }
    cout << endl;

    cout << "  Tamanho da linha: " << linhas[0].tamanho << endl;
    cout << "  Soma das viabilidades: " << linhas[0].soma_viabilidade << endl;
    cout << "  Media de viabilidade: " << linhas[0].media_viabilidade << endl;
    cout << "  Demanda atendida: " << linhas[0].demanda_atendida << endl;
    cout << "  Custo da linha: " << linhas[0].custo << endl;
    cout << "  Indice da linha: " << linhas[0].indice_construcao << endl;

    cout << "-------------------------------------" << endl;

    return 0;
}