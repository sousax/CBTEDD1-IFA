#include <iostream>
#include <locale.h>
using namespace std;

struct No {
	int dado;
	struct No *prox;	
};

struct Pilha {
	No *topo;
};

Pilha* init() {
	Pilha *p = new Pilha;
	p->topo = NULL;
	return p;
}

int isEmpty(Pilha *p) {
	return (p->topo == NULL);
}

int count(Pilha *p) {
	int i = 0;
	No *no;
	no = p->topo;
	while (no != NULL) {
		i++;
		no = no->prox;
	}
	return i;
}

void print(Pilha *p) {
	No *no;
	no = p->topo;
	while (no != NULL) {
		cout << no->dado << endl;
		no = no->prox;
	}
	cout << "--------------------" << endl;
}

void freePilha(Pilha *p) {
	No *no;
	no = p->topo;
	while (no != NULL) {
		No *aux = no->prox;
		delete no;
		no = aux;
	}	
	delete p;
}

void push(Pilha *p, int v) {
	No *no = new No;
	no->dado = v;
	no->prox = p->topo;
	p->topo = no;
}

int pop(Pilha *p) {
	int v;
	if (!isEmpty(p)) {
		No *no = p->topo;
		v = no->dado;
		p->topo = no->prox;
		delete no;
		return v;
	}
	return -1;
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	Pilha *pilhaPar = init();
	Pilha *pilhaImpar = init();
	int numeroDigitado;
	int ultimoNumero = 0;

	cout << "Digite 30 números inteiros em ordem crescente:" << endl;
	for (int i = 0; i < 30; ++i) {
		do {
			cout << "Digite o " << i + 1 << "º número: ";
			cin >> numeroDigitado;
			if (numeroDigitado <= ultimoNumero) {
				cout << "O número deve ser maior que o anterior. Tente novamente." << endl;
			}
		} while (numeroDigitado <= ultimoNumero);

		ultimoNumero = numeroDigitado;

		if (numeroDigitado % 2 == 0) {
			push(pilhaPar, numeroDigitado);
		} else {
			push(pilhaImpar, numeroDigitado);
		}
	}
	cout << "--------------------" << endl;
	cout << "Números pares empilhados:" << endl;
	print(pilhaPar);
	cout << "Números ímpares empilhados:" << endl;
	print(pilhaImpar);

	cout << "Desempilhando e mostrando os números na ordem decrescente:" << endl;
	
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