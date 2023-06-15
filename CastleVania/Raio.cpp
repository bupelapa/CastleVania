#include "Raio.hpp"

#include "Animacao.hpp"
#include "GerenciadorGrafico.hpp"

Raio::Raio(sf::Vector2f pos) :
Projetil(ID::boladefogo, pos, sf::Vector2f(RAIO_LARGURA, RAIO_ALTURA), RAIO_DANO) {
    setAparece(false);
    inicializaSprite();
}

Raio::~Raio() {
}

void Raio::atualiza(float dt) {
    if (getAparece()) {
        atualizaAtivo(dt);
        mudarPosicao(Vector2f(velocidade.x * dt + posicao.x, velocidade.y * dt + posicao.y));
        sprite->atualiza(0, dt, olhandoEsquerda(), posicao);
    }
}

void Raio::inicializaSprite() {
    sprite->inicializarTextura(PATH_RAIO_TEXTURA, sf::Vector2u(3, 1));
}

