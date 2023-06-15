#include "BolaDeFogo.hpp"

#include "Animacao.hpp"
#include "GerenciadorGrafico.hpp"

BolaDeFogo::BolaDeFogo(sf::Vector2f pos) :
Projetil(ID::boladefogo, pos, sf::Vector2f(BOLADEFOGO_LARGURA, BOLADEFOGO_ALTURA), BOLADEFOGO_DANO) {
    setAparece(false);
    inicializaSprite();
}

BolaDeFogo::~BolaDeFogo() {
}

void BolaDeFogo::atualiza(float dt) {
    if (getAparece()) {
        atualizaAtivo(dt);
        mudarPosicao(Vector2f(velocidade.x * dt + posicao.x, velocidade.y * dt + posicao.y));
        sprite->atualiza(0, dt, olhandoEsquerda(), posicao);
    }
}

void BolaDeFogo::inicializaSprite() {
    sprite->inicializarTextura(PATH_BOLADEFOGO_TEXTURA, sf::Vector2u(3, 1));
}
