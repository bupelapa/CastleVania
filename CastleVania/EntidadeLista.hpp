#pragma once

#include "Personagem.hpp"
#include "Entidade.hpp"
#include "Lista.hpp"
#include "Obstaculo.hpp"
#include "Projetil.hpp"
#include "stdafx.h"

class EntidadeLista {
private:
    Lista<Entidade> list;

public:
    EntidadeLista();
    ~EntidadeLista();

    void atualizaTudo(float dt);
    void renderizaTudo();
    void addEntidade(Entidade* pNovo);
    void removeEntidade(Entidade* pDel);
    void deleteAll();
    void deleteAllMenosJogador();
    const Lista<Entidade>* getLista() { return &list; }
    int getTamanho() { return list.comprimento()  ;} //retorna o tamanho da lista
    Entidade* operator[](int x);
};

