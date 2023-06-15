#pragma once

#include "PlanoDeFundo.hpp"
#include "GerenciadorColisao.hpp"
#include "Entidade.hpp"
#include "EntidadeLista.hpp"
#include "GerenciadorEvento.hpp"
#include "GerenciadorGrafico.hpp"
#include "Jogador.hpp"
#include "stdafx.h"

#define PATH_PLANODEFUNDO_PRIMEIRONIVEL "./imagens/FundoNivelUm.png"
#define PATH_PLANODEFUNDO_SEGUNDONIVEL "./imagens/FundoNivelDois.png"

class Nivel {
private:
    GerenciadorGrafico* Ggrafico;
    EntidadeLista* _lista;
    Jogador *jogador1, *jogador2;
    GerenciadorColisao colis;
    sf::Vector2u nivelMapaTamanho;
    PlanoDeFundo back;
    GerenciadorEvento* pGerenEvento;
    int nivelRodando;
    char path[100];
    int chegouFinal;

public:
    Nivel(const char* path = "", Jogador* j1 = NULL, Jogador* j2 = NULL, sf::Vector2u nivelTamanho = sf::Vector2u(0, 0));
    virtual ~Nivel();
    void exec(float dt);

    Jogador* getJ1() const { return jogador1; }
    Jogador* getJ2() const { return jogador2; }
    void setJ1(Jogador* j1) { jogador1 = j1; }
    void setJ2(Jogador* j2) { jogador2 = j2; }
    GerenciadorColisao* getCols() { return &colis; }
    void renderizaTudo();
    void centerView();
    int nivelTaRodando() const { return nivelRodando; }
    void addEntidade(Entidade* ent) { _lista->addEntidade(ent); }
    void saveNvl();
    void setFim(int end) { chegouFinal = end; }
    int getNumNivel();
};

