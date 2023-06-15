#pragma once
#include "Inimigo.hpp"

class Animacao;
class Jogador;

#define BOSS_PATH "./imagens/anjo.png"
#define BOSS_VELOCIDADE 160
#define BOSS_MOTIONX_MAX 500
#define BOSS_MOTIONX_MIN 100
#define BOSS_ALTURA 140
#define BOSS_LARGURA 50
#define BOSS_VIDA 8000
#define BOSS_DANO 50
#define BOSS_ATAQUEX 300
#define MAX_VAR_ALTURA_BOSS 200
#define MAX_VAR_DISTANCIA_BOSS 200
#define BOSS_RAIO_VELOCIDADE 600

class Boss : public Inimigo {
private:
    Raio* raio;
    static const float tempoAtaque;
    int maxHeight;
    int minHeight;
    int maxDistance;
    int minDistance;

public:
    Boss(sf::Vector2f pos = sf::Vector2f(0.f, 0.f), Raio* pRaio = NULL, Jogador* pJogador1 = NULL, Jogador* pJogador2 = NULL, int minH = 0, int maxH = 0, int minD = 0, int maxD = 0);
    ~Boss();
    void inicializaSprite();
    void atualiza(float dt);
    void save();
    void ataca();
    void segueJogador();
    void atualizaSprite(float dt);
};
