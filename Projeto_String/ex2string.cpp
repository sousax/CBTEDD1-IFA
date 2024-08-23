#include <iostream>
#include <string>
#include <locale.h>
using namespace std;

int main(int argc, char** argv) {
    setlocale(LC_ALL, "");

    string mensagem;
    cout << "Insira uma mensagem para verificar se � um pal�ndromo: ";
    getline(cin, mensagem);

    string stringNoVoid;
    for (int i = 0; i < mensagem.length(); i++) {
        char c = mensagem[i];
        if (!isspace(c)) {
            stringNoVoid += c;
        }
    }

    bool palindromo = true;
    int tam = stringNoVoid.length();
    for (int i = 0; i < tam / 2; i++) {
        if (tolower(stringNoVoid[i]) != tolower(stringNoVoid[tam - i - 1])) {
            palindromo = false;
            break;
        }
    }

    if (palindromo) {
        cout << "A mensagem \"" << mensagem << "\" � um pal�ndromo." << endl;
    } else {
        cout << "A mensagem \"" << mensagem << "\" n�o � um pal�ndromo." << endl;
    }

    return 0;
}
