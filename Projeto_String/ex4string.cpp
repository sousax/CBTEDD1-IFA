#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Fun��o para transformar um nome no formato de cita��o bibliogr�fica
string transformarNome(const string& nome) {
    string nomeFormatado;
    istringstream ss(nome);
    string parte;
    vector<string> partes;

    // Divide o nome em partes separadas por espa�os
    while (ss >> parte) {
        partes.push_back(parte);
    }

    // Se n�o h� partes suficientes, retorna o nome original
    if (partes.size() < 2) {
        return nome;
    }

    // Adiciona o �ltimo sobrenome em mai�sculas seguido por v�rgula
    string ultimoSobrenome = partes.back();
    for (size_t i = 0; i < ultimoSobrenome.size(); ++i) {
        ultimoSobrenome[i] = toupper(ultimoSobrenome[i]);
    }
    nomeFormatado += ultimoSobrenome + ", ";

    // Adiciona o primeiro nome sem abrevia��o
    string primeiroNome = partes.front();
    primeiroNome[0] = toupper(primeiroNome[0]); // Primeira letra do primeiro nome em mai�scula
    nomeFormatado += primeiroNome;

    // Adiciona as iniciais abreviadas dos sobrenomes do meio
    for (size_t i = 1; i < partes.size() - 1; ++i) {
        nomeFormatado += ' ';
        nomeFormatado += toupper(partes[i][0]);
        nomeFormatado += ".";
    }

    nomeFormatado += " "; // Adiciona um espa�o no final

    return nomeFormatado;
}

int main() {
    ifstream arquivoEntrada("nomes.txt");
    if (!arquivoEntrada.is_open()) {
        cout << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }

    ofstream arquivoSaida("nomes_formatados.txt");
    if (!arquivoSaida.is_open()) {
        cout << "Erro ao criar o arquivo de sa�da." << endl;
        return 1;
    }

    // Ler os nomes do arquivo de entrada e transform�-los
    string nome;
    while (getline(arquivoEntrada, nome)) {
        // Transforma o nome no formato de cita��o bibliogr�fica
        string nomeFormatado = transformarNome(nome);
        // Escreve o nome formatado no arquivo de sa�da
        arquivoSaida << nomeFormatado << endl;
    }

    arquivoEntrada.close();
    arquivoSaida.close();

    cout << "Nomes formatados com sucesso!" << endl;

    return 0;
}
