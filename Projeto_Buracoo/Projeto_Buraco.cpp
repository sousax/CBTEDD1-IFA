#include <iostream>
#include <ctime> // Para time()
#include <cstdlib> // Para srand() e rand()
#include <string>
#include <locale.h>
#include <sstream> // Para ostringstream

using namespace std;

string intToString(int value) {
    ostringstream oss;
    oss << value;
    return oss.str();
}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, ""); 

    // Inicializa o gerador de números aleatórios uma vez
    srand(time(0)); 

    string baralho[2][52];
    string mao[4][11];
    bool cartasDistribuidas[2][52] = {false};

    // Preenchendo o baralho
    for (int n = 0; n < 4; n++)
    {
        for (int c = 0; c < 13; c++)
        {
            for (int b = 0; b < 2; b++)
            {
                baralho[b][n * 13 + c] = intToString(n + 1) + "-" + (c < 9 ? "0" : "") + intToString(c + 1) + "-" + intToString(b + 1);
            }
        }
    }

    // Distribuindo as cartas
    for (int j = 0; j < 4; j++)
    {
        for (int c = 0; c < 11; c++)
        {
            int n = rand() % 2; 
            int i = rand() % 52; 

            // Garante que a carta ainda não foi distribuída
            while (cartasDistribuidas[n][i])
            {
                n = rand() % 2;
                i = rand() % 52;
            }
            mao[j][c] = baralho[n][i]; 
            cartasDistribuidas[n][i] = true; 
        }
    }

    // Exibe as mãos dos jogadores
    for (int j = 0; j < 4; j++)
    {
        cout << "Mão do jogador " << j + 1 << ":" << endl;
        for (int c = 0; c < 11; c++)
        {
            cout << mao[j][c] << endl;
        }
        cout << endl;
    }
    return 0;
}
