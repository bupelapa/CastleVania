#pragma once
#include "Inimigo.hpp"

class Animacao;

#define GHOUL_PATH "./imagens/ghoul.png"
#define GHOUL_VELOCIDADEX 175
#define GHOUL_MOTIONX_MAX 500
#define GHOUL_MOTIONX_MIN 100
#define GHOUL_VIDA 1000
#define GHOUL_DANO 20
#define GHOUL_ATAQUEX 120

class Ghoul : public Inimigo {
private:
    static const float tempoAtaque;
    float tempoAtacando;

public:
    Ghoul(sf::Vector2f pos, Jogador* pJogador1 = NULL, Jogador* pJogador2 = NULL);
    ~Ghoul();
    void inicializaSprite();
    void atualiza(float dt);
    void save();
    void ataca();
    void atualizaSprite(float dt);
    void comportamentoGhoul();
};
