#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Bairro {
    int index;
    string nome;
    int viabilidade;
    bool viavel = false;
};

void obter_bairros_viaveis(Bairro bairros[], int size) {
    for (int i = 0; i < size; i++) {
        if (bairros[i].viabilidade >= 70) {
            bairros[i].viavel = true;
        }
    }
}

int main() {
    Bairro bairros[5] = {{0, "a", 80}, {1, "ab", 40}, {2, "ac", 90}, {3, "ad", 70}, {4, "ae", 20}};
    Bairro* bairros_viaveis;

    for (int i = 0; i < 5; i++) {
        cout << bairros[i].index << endl;
    }

    obter_bairros_viaveis(bairros, 5);

    for (int i = 0; i < 5; i++) {
        if (bairros[i].viavel == true) {
            cout << "Index: " << bairros[i].index << " | Viabilidade = " << bairros[i].viabilidade << endl;
        }
    }

    return 0;
}