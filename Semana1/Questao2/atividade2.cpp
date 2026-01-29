#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

// ------------------------------------------------------------
// Constante do número de amostras
// ------------------------------------------------------------

const int N = 150;

// ------------------------------------------------------------
// Função para ler o arquivo de dados do satélite e armazenar
// cada coluna em um vetor diferente para trabalhar.
//
// Retorna true se a leitura bem-sucedida, e false se tiver 
// erro ao abrir ou ler o arquivo
// ------------------------------------------------------------

bool carregarDadosCSV(
    const string& nomeArquivo,
    int time_step[],
    double altitude[],
    double velocity[],
    double temperature[],
    double power[],
    int tamanho
) {
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        return false;
    }

    string linha;

    // Ignora o cabeçalho
    getline(arquivo, linha);

    int i = 0;

    while (getline(arquivo, linha) && i < tamanho) {
        stringstream ss(linha);
        string campo;

        getline(ss, campo, '	');
        time_step[i] = stoi(campo);

        getline(ss, campo, '	');
        altitude[i] = stod(campo);

        getline(ss, campo, '	');
        velocity[i] = stod(campo);

        getline(ss, campo, '	');
        temperature[i] = stod(campo);

        getline(ss, campo, '	');
        power[i] = stod(campo);

        i++;
    }

    arquivo.close();
    return true;
}

void filtrar(double dados[N], double _filtrada[N]) {
    _filtrada[0] = dados[0];

    for (int i = 1; i < N; i++) {
        double filtro = (dados[i] + _filtrada[i - 1]) / 2;

        _filtrada[i] = filtro;
    }
}

bool estabilidade(double _filtrada[N]) {
    for (int i = 0; i < N-1; i++) {
        if (abs(_filtrada[i + 1] - _filtrada[i]) >= 3) {
            return false;
        }
    }

    return true;
}

int main() {

    int time_step[N];
    double altitude[N];
    double velocity[N];
    double temperature[N];
    double power[N];

    double altitude_filtrada[N];
    double velocity_filtrada[N];
    double temperature_filtrada[N];
    double power_filtrada[N];

    // ------------------------------------------------------------
    // Leitura dos dados do CSV do Zarya; como a função retorna
    // true ou false para o sucesso da operação, essa "resposta""
    // é guardada na variável "carregamento". Se tivermos sucesso,
    // printa "Sucesso ao carregar o arquivo de dados.", senão
    // printa "Erro ao carregar o arquivo de dados." e retorna um
    // número de erro (neste caso, 1) para encerrar o programa.
    // ------------------------------------------------------------

    bool carregamento = carregarDadosCSV("Zarya.csv",
                                         time_step,
                                         altitude,
                                         velocity,
                                         temperature,
                                         power,
                                         N);

    if (!carregamento) {
        cout << "Erro ao carregar o arquivo de dados." << endl;
        return 1;
    } else {
        cout << "Sucesso ao carregar o arquivo de dados." << endl;
    }

    // ------------------------------------------------------------
    // A partir daqui, você deve aplicar o filtro nos vetores que
    // guardam os dados (sugiro que crie uma função para o filtro),
    // guarde as leituras filtradas nos vetores "_filtrada", 
    // verifique a estabilidade (se de um dado pro outro não 
    // tiveram grandes saltos de valores, na qual sinta-se livre
    // pra julgar o que é um salto grande), e ao final, retorne as
    // colunas (altitude, velocidade, etc) que ficaram estaveis e 
    // não estaveis.
    // ------------------------------------------------------------

    // Aplicação de Filtros
    filtrar(altitude, altitude_filtrada);
    filtrar(velocity, velocity_filtrada);
    filtrar(temperature, temperature_filtrada);
    filtrar(power, power_filtrada);

    cout << "\n\nCOLUNAS APOS APLICACAO DO FILTRO\n\n";
    
    cout << left
     << setw(10) << "Time"
     << setw(15) << "Altitude"
     << setw(15) << "Velocity"
     << setw(15) << "Temperature"
     << setw(15) << "Power"
     << endl;

    cout << string(70, '-') << endl;
    cout << fixed << setprecision(2);

    for (int i = 0; i < N; i++) {
        cout << left
             << setw(10) << time_step[i]
             << setw(15) << altitude_filtrada[i]
             << setw(15) << velocity_filtrada[i]
             << setw(15) << temperature_filtrada[i]
             << setw(15) << power_filtrada[i]
             << endl;
    }

    cout << "\n\n RESULTADO DE ESTABILIDADE ( DIFERENCA <= 3 )\n\n";
    
    if (estabilidade(altitude_filtrada)) {
        cout << " Altitude Estavel " << endl;
    } else cout << " Altitude Instavel" << endl;

    if (estabilidade(velocity_filtrada)) {
        cout << "-> Velocity Estavel " << endl;
    } else cout << "-> Velocity Instavel" << endl;

    if (estabilidade(temperature_filtrada)) {
        cout << "-> Temperature Estavel " << endl;
    } else cout << "-> Temperature Instavel" << endl;

    if (estabilidade(power_filtrada)) {
        cout << "-> Power Estavel " << endl;
    } else cout << "-> Power Instavel" << endl;

    return 0;
}