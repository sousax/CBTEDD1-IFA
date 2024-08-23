#include <iostream>
#include <locale.h>
#include <string>

using namespace std;

struct No {
    int dado;
    No *prox;
};

struct Fila {
    No *ini;
    No *fim;
};

Fila* init() {
    Fila *f = new Fila;
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

int isEmpty(Fila *f) {
    return (f->ini == NULL);
}

void geraSenha(Fila* f, int v) {
    No *no = new No;
    no->dado = v;
    no->prox = NULL;
    if (isEmpty(f)) {
        f->ini = no;
    } else {
        f->fim->prox = no;
    }
    f->fim = no;
}

int alteraSenha(Fila* f) {
    if (isEmpty(f)) {
        return -1; 
    }
    No *no = f->ini;
    int ret = no->dado;
    f->ini = no->prox;
    if (f->ini == NULL) {
        f->fim = NULL;
    }
    delete no;
    return ret;
}

int count(Fila* f) {
    int qtde = 0;
    No *no = f->ini;
    while (no != NULL) {
        qtde++;
        no = no->prox;
    }
    return qtde;
}

void print(Fila* f) {
    No *no = f->ini;
    cout << "-- Qtde de elementos: " << count(f) << endl;
    while (no != NULL) {
        cout << no->dado << endl;
        no = no->prox;
    }
}

void freeFila(Fila* f) {
    No* no = f->ini;
    while (no != NULL) {
        No* temp = no->prox;
        delete no;
        no = temp;
    }
    delete f;
}

struct GuicheNode {
    int id;
    Fila* senhasAtendidas;
    GuicheNode* next;
};

struct ListaGuiches {
    GuicheNode* head;
};

ListaGuiches* initGuiches() {
    ListaGuiches* lista = new ListaGuiches;
    lista->head = NULL;
    return lista;
}

void adicionarGuiche(ListaGuiches* lista, int id) {
    GuicheNode* novo = new GuicheNode;
    novo->id = id;
    novo->senhasAtendidas = init();
    novo->next = lista->head;
    lista->head = novo;
}

GuicheNode* encontrarGuiche(ListaGuiches* lista, int id) {
    GuicheNode* aux = lista->head;
    while (aux != NULL) {
        if (aux->id == id) {
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}

void freeListaGuiches(ListaGuiches* lista) {
    GuicheNode* no = lista->head;
    while (no != NULL) {
        GuicheNode* temp = no->next;
        freeFila(no->senhasAtendidas);
        delete no;
        no = temp;
    }
    delete lista;
}

void listarSenhasAtendidas(GuicheNode* guiche) {
    cout << "Senhas atendidas pelo guichê " << guiche->id << ":" << endl;
    print(guiche->senhasAtendidas);
}

int main() {
    setlocale(LC_ALL, "");

    Fila* senhasGeradas = init();
    ListaGuiches* listaGuiches = initGuiches();
    int opcao;
    int senha = 0;

    do {
        cout << "Existem: " << count(senhasGeradas) << " senhas para serem atendidas" << endl;
        int numGuiches = 0;
        GuicheNode* tempGuiche = listaGuiches->head;
        while (tempGuiche != NULL) {
            numGuiches++;
            tempGuiche = tempGuiche->next;
        }
        cout << "Número de guichês abertos: " << numGuiches << endl;

        cout << "Escolha uma das opções abaixo:" << endl;
        cout << "0. Sair." << endl;
        cout << "1. Gerar senha." << endl;
        cout << "2. Abrir guichê." << endl;
        cout << "3. Realizar atendimento." << endl;
        cout << "4. Listar senhas atendidas." << endl;
        cin >> opcao;

        if (opcao == 0 && !isEmpty(senhasGeradas)) {
            cout << "Existem senhas para serem atendidas. Finalize elas para sair." << endl;
            opcao = -1;
        }

        switch (opcao) {
            case 0:
                break;

            case 1:
                senha++;
                geraSenha(senhasGeradas, senha);
                cout << "Sua senha: " << senha << endl;
                break;

            case 2: {
                int idGuiche;
                cout << "Digite o ID do novo guichê: ";
                cin >> idGuiche;
                adicionarGuiche(listaGuiches, idGuiche);
                cout << "Guichê " << idGuiche << " adicionado." << endl;
                break;
            }

            case 3: {
                int idGuiche;
                cout << "Digite o ID do guichê que está chamando a senha: ";
                cin >> idGuiche;
                GuicheNode* guiche = encontrarGuiche(listaGuiches, idGuiche);
                if (guiche == NULL) {
                    cout << "Guichê não encontrado." << endl;
                } else {
                    int senhaAtendida = alteraSenha(senhasGeradas);
                    if (senhaAtendida <= 0) {
                        cout << "Não existem senhas para atender." << endl;
                    } else {
                        geraSenha(guiche->senhasAtendidas, senhaAtendida);
                        cout << "Senha atendida pelo guichê " << idGuiche << ": " << senhaAtendida << endl;
                    }
                }
                break;
            }

            case 4: {
                int idGuiche;
                cout << "Digite o ID do guichê para listar senhas atendidas: ";
                cin >> idGuiche;
                GuicheNode* guiche = encontrarGuiche(listaGuiches, idGuiche);
                if (guiche == NULL) {
                    cout << "Guichê não encontrado." << endl;
                } else {
                    listarSenhasAtendidas(guiche);
                }
                break;
            }

            default:
                cout << "ERRO!!! Tente novamente." << endl;
                break;
        }

    } while (opcao != 0);

    cout << "Encerrando o programa." << endl;
    cout << "Quantidade de senhas atendidas: ";
    int totalAtendidas = 0;
    GuicheNode* tempGuiche = listaGuiches->head;
    while (tempGuiche != NULL) {
        totalAtendidas += count(tempGuiche->senhasAtendidas);
        tempGuiche = tempGuiche->next;
    }
    cout << totalAtendidas << endl;

    freeFila(senhasGeradas);
    freeListaGuiches(listaGuiches);

    return 0;
}