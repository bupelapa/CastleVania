#include "EntidadeLista.hpp"

EntidadeLista::EntidadeLista() :
list() {
}

EntidadeLista::~EntidadeLista() {
    list.clear();
}

/* Cicla a lista chamando a função de atualizar para cada elemento */
void EntidadeLista::atualizaTudo(float dt) {
    Entidade* pAux;
    for (int i = 0; i < list.comprimento(); i++) {
        pAux = list[i];
        pAux->atualiza(dt);
    }
}

/* Cicla a lista chamando a função de renderiza para cada elemento. */
void EntidadeLista::renderizaTudo() {
    Entidade* pAux;
    for (int i = 0; i < list.comprimento(); i++) {
        if (list[i]->getAparece()) {
            pAux = list[i];
            pAux->renderiza();
        }
    }
}

/* adiciona um Entidade* a lista. */
void EntidadeLista::addEntidade(Entidade* pNovo) {
    if (pNovo == NULL) {
        cout << "Pointer para Entidade e NULL em addEntidade." << endl;
        exit(7);
    }
    list.append(pNovo);
}

/* Remove uma Entidade especifica dado por um ponteiro. Nao deleta.*/
void EntidadeLista::removeEntidade(Entidade* pDel) {
    if (pDel == NULL) {
        cout << "Pointer para Entidade é NULL em removeEntidade." << endl;
        exit(7);
    }
    list.remove(pDel);
}

/* Deleta a lista inteira e desloca suas entidades. */
void EntidadeLista::deleteAll() {
    list.clear();
}

void EntidadeLista::deleteAllMenosJogador() {
    for (int i = 0; i < list.comprimento(); i++) {
        if ((list[i]->getId() != ID::jogador)) {
            list.remove(list[i]);
        }
    }
}

/* Retorna pointer de Entidade da lista. */
Entidade* EntidadeLista::operator[](int x) {
    if (x >= list.comprimento() || x < 0) {
        std::cout << "ERROR: Erro de segmentacao em Entidade. Ultrapassou limites." << std::endl;
        exit(1);
    }
    Entidade* aux = list[x];
    return aux;
}
