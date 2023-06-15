#include "Botao.hpp"

#include "Animacao.hpp"
#include <math.h>
#include <string.h>

Botao::Botao(sf::Vector2f pos) :
Ent(ID::botao, pos),
hover(false) {
    inicializaSprite();
    pGerenciadorGrafico = GerenciadorGrafico::getGerenciadorGrafico();
}

Botao::~Botao() {
}

void Botao::setMensagem(const char* m) {
    texto.setString(m);

    texto.setFont(*pGerenciadorGrafico->getFont());
    texto.setCharacterSize(TEXT_SIZE);

    sf::FloatRect textoRect = texto.getLocalBounds();
    texto.setOrigin(textoRect.left + textoRect.width / 2.0f, textoRect.top + textoRect.height / 2.0f);
    texto.setPosition(posicao);
    texto.setFillColor(sf::Color::White);
}

void Botao::inicializaSprite() {
    sprite->inicializarTextura(BOTAO_PATH, sf::Vector2u(1, 2));
}

void Botao::renderiza() {
    if (hover)
        sprite->atualiza(0, 0, false, posicao);
    else
        sprite->atualiza(1, 0, false, posicao);

    sprite->renderiza();

    pGerenciadorGrafico->desenhaElemento(&texto);
}

