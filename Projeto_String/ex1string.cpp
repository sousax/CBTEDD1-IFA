#include <iostream>
#include <windows.h>
#include <string>
using namespace std;



// Fun��o para posicionar o cursor na tela
void gotoxy(short x, short y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main(int argc, char** argv) {
    string msg;
    
    // Solicita ao usu�rio que digite uma palavra para ser exibida no centro da tela
    cout << "Insire uma palavra para ser exibida no centro da tela: ";
    getline(cin, msg);

    // Calcula a posi��o inicial para centralizar a mensagem na tela
    int centraliza = (80 - msg.length()) / 2;

    // Exibe a mensagem centralizada na linha 5
    gotoxy(centraliza, 5);
    cout << msg;

    // Simula a queda da mensagem at� a linha 20
    for (int i = 0; i < msg.length(); i++) {
        for (int j = 5; j <= 20; j++) {
            // Limpa a posi��o atual
            gotoxy(centraliza + i, j);
            cout << " ";

            // Exibe a letra da mensagem na posi��o correta
            if (j >= 5 + i) {
                gotoxy(centraliza + i, j);
                cout << msg[i];
            }
        }
    }

    return 0;
}