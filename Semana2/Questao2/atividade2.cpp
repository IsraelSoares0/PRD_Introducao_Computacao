#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

// Gravidade constante (m/s²)
const double G = 9.8;

// ------------------------------------------------------------
// Função para gerar um número aleatório
// Você deve passar para a função, os dois valores (min e max)
// de intervalo na qual o número pode se encontrar.
// ------------------------------------------------------------

double aleatorio(double min, double max) {
    return min + (max - min) * (rand() / (double) RAND_MAX);
}

// ------------------------------------------------------------
// Função para converter um ângulo de graus para radianos
// ------------------------------------------------------------

double grausParaRadianos(double graus) {
    return graus * 3.141592653589793 / 180.0;
}

// ------------------------------------------------------------
// Função para calcular o alcance R com base na equação
// R = (v² * sin(2θ)) / g
// Com a gravidade constante (9,8 m/s²)
// ------------------------------------------------------------

double calcularAlcance(double v, double theta) {
    double thetaRad = grausParaRadianos(theta);
    return (v * v * sin(2 * thetaRad)) / G;
}

int main() {
    // Setando a seed
    random_device rd;
    srand(rd());

    int N;              // Número de simulações
    double v0;          // Velocidade nominal
    double deltaV;      // Variação máxima da velocidade
    double theta0;      // Ângulo nominal
    double deltaTheta;  // Variação máxima do ângulo
    int K;              // Número de regiões (bins) da distribuição

    cout << "Digite o numero de simulacoes (N): ";
    cin >> N;

    cout << "Digite a velocidade nominal v0 (m/s): ";
    cin >> v0;

    cout << "Digite a variacao maxima da velocidade Δv (m/s): ";
    cin >> deltaV;

    cout << "Digite o angulo nominal θ0 (graus): ";
    cin >> theta0;

    cout << "Digite a variacao maxima do angulo Δθ (graus): ";
    cin >> deltaTheta;

    cout << "Digite o numero de regioes K para a distribuicao: ";
    cin >> K;

    // ------------------------------------------------------------
    // A partir daqui, você deve gerar valores aleatórios 
    // de v e θ dentro dos intervalos (use a função "aleatorio"
    // que foi criada), calcular o alcance para cada simulação,
    // armazenar/analisar os resultados, e construir a distribuição 
    // do alcance em K regiões
    // ------------------------------------------------------------

    streambuf* bufferOriginal = cout.rdbuf();
    ofstream arquivo("saida.txt");

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo saida.txt" << endl;
        return 1;
    }

    cout.rdbuf(arquivo.rdbuf());

    double Rmin;
    double Rmax;
    double v;
    double theta;
    double R;

    vector<double> raios;
    vector<int> regioes(K, 0);

    v = aleatorio(v0 - deltaV, v0 + deltaV);
    theta = aleatorio(theta0 - deltaV, theta0 + deltaTheta);
    R = calcularAlcance(v, theta);
    raios.push_back(R);

    Rmin = R;
    Rmax = R;

    for (int i = 1; i < N; i++) {
        v = aleatorio(v0 - deltaV, v0 + deltaV);
        theta = aleatorio(theta0 - deltaV, theta0 + deltaTheta);
        R = calcularAlcance(v, theta);

        raios.push_back(R);
        
        if (R > Rmax) {
            Rmax = R;
        }
        if (R < Rmin) {
            Rmin = R;
        }
    }

    cout << "--------- Parametros Utilizados ---------" << endl << endl;
    cout << "   -> Numero de simulacoes = " << N << endl;
    cout << "   -> Velocidade nominal = " << v0 << endl;
    cout << "   -> Variacao de velocidade = " << deltaV << endl;
    cout << "   -> Angulo nominal = " << theta0 << endl;
    cout << "   -> Variacao maxima do angulo = " << deltaTheta << endl;
    cout << "   -> Numero de regioes para analise da distribuicao = " << K << endl << endl;

    cout << "Rmin = " << Rmin << " | Rmax = " << Rmax << endl << endl;;

    double particao = (Rmax - Rmin) / K;
    Rmax = Rmin + particao;

    cout << "Tamanho da particao: " << particao << endl << endl;

    for (int i = 0; i < K; i++) {

        for (int j = 0; j < raios.size(); j++) {
            if (raios[j] >= Rmin && raios[j] < Rmax) {
                regioes[i]++;
            }
        }

        double porcentagem = regioes[i] / static_cast<double>(N);

        cout << fixed << setprecision(1);
        cout << "Particao: " << i << " [" << Rmin << " - " << Rmax << "]: " << regioes[i] << " lançamentos (" << porcentagem * 100 << "%)" << endl;;

        Rmin = Rmax;
        Rmax = Rmax + particao;
    }

    cout << endl;

    cout.rdbuf(bufferOriginal);
    arquivo.close();

    return 0;
}