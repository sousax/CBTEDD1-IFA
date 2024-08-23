#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main() {
    
    ifstream arquivoEntrada("nomes.txt");
    if (!arquivoEntrada.is_open()) {
        cout << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }


    ofstream arquivoSaida("nomes_agenda.txt");
    if (!arquivoSaida.is_open()) {
        cout << "Erro ao abrir ou criar o arquivo de saída." << endl;
        return 1;
    }

    
    string nome;
    while (getline(arquivoEntrada, nome)) {
      
        size_t posUltimoEspaco = nome.find_last_of(' ');
        if (posUltimoEspaco == string::npos) {
           
            arquivoSaida << nome << endl;
        } else {
          
            string ultimoSobrenome = nome.substr(posUltimoEspaco + 1);
            string restoNome = nome.substr(0, posUltimoEspaco);

            
            string nomeFormatado = ultimoSobrenome + ", " + restoNome;

      
            arquivoSaida << nomeFormatado << std::endl;
        }
    }


    arquivoEntrada.close();
    arquivoSaida.close();

    cout << "Nomes formatados com sucesso!" << endl;

    return 0;
}