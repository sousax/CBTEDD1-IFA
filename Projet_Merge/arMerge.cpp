#include <iostream>
#include <locale.h>
using namespace std;

#define MAX 10

struct Pilha {
	int qtde;
	int elementos[MAX];
};

Pilha* init() {
	Pilha *p = new Pilha;
	p->qtde = 0;
	return p;
}

int isEmpty(Pilha *p) {
	return (p->qtde == 0);
}

int count(Pilha *p) {
	return (p->qtde);
}

void freePilha(Pilha *p) {
	delete(p);
}

int push(Pilha *p, int v) {
	int podeEmpilhar = (p->qtde < MAX);
	if (podeEmpilhar) {
			p->elementos[p->qtde++] = v;
	}
	return podeEmpilhar;
}

int pop(Pilha *p) {
	int podeDesempilhar = (p->qtde > 0);
	int v;
	if (podeDesempilhar) {
		v = p->elementos[--p->qtde];
	}
	else {
		v = -1;
	}
	return v;
}

void print(Pilha *p) {
	cout << "Qtde de elementos: " << count(p) << endl;
	for(int i = p->qtde-1; i>=0; --i) {
			cout << p->elementos[i] << endl;
	}
	cout << "--------------------" << endl;
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");

	Pilha *pilhaPar = init();
	Pilha *pilhaImpar = init();

	int numeroAnterior = 0;
	int numeroDigitado;
	int contador = 0;

	while (contador < MAX) {
		cout << "Digite o " << contador + 1 << "º número: ";
		cin >> numeroDigitado;
		if (numeroDigitado > numeroAnterior) {
				if (numeroDigitado % 2 == 0) {
						push(pilhaPar, numeroDigitado);
				} else {
						push(pilhaImpar, numeroDigitado);
				}
				numeroAnterior = numeroDigitado;
				contador++;
		} else {
				cout << "Digite um número maior do que o anterior." << endl;
		}
	}
	cout << "--------------------" << endl;
	cout << "Valores pares empilhados:" << endl;
	print(pilhaPar);
	cout << "Valores ímpares empilhados:" << endl;
	print(pilhaImpar);

	cout << "Desempilhando e exibindo valores em ordem decrescente:" << endl;
	cout << "Pilha par: " << endl;
	while (!isEmpty(pilhaPar)) {
			cout << pop(pilhaPar) << endl;
	}
	cout << "Pilha ímpar: " << endl;
	while (!isEmpty(pilhaImpar)) {
			cout << pop(pilhaImpar) << endl;
	}

	freePilha(pilhaPar);
	freePilha(pilhaImpar);

	return 0;
}