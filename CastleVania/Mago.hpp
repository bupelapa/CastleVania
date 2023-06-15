#pragma once
#include "Inimigo.hpp"

#define Mago_PATH "./imagens/mago.png"
#define MAGO_VIDA 1200
#define MAGO_DANO 25
#define MAGO_VELOCIDADE 100
#define MAX_VAR_ALTURA 200
#define MAGO_ATAQUEX 600
#define MAGO_BOLADEFOGO_VELOCIDADE 500


class Animacao;
class Jogador;

class Mago : public Inimigo {
private:
    BolaDeFogo* boladefogo;
    static const float tempoAtaque;
    int maxHeight;
    int minHeight;

public:
    Mago(sf::Vector2f pos = sf::Vector2f(0.f, 0.f), BolaDeFogo* bfogo = NULL, Jogador* pJogador1 = NULL, Jogador* pJogador2 = NULL, int minH = 0, int maxH = 0);
    ~Mago();
    void inicializaSprite();
    void atualiza(float dt);
    void ataca();
    void save();
    void segueJogador();
    void atualizaSprite(float dt);
};
