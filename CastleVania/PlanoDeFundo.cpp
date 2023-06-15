#include "PlanoDeFundo.hpp"

#include "Animacao.hpp"

PlanoDeFundo::PlanoDeFundo(sf::Vector2f pos, const char* path) :
Ent(ID::PlanoDeFundo, pos) {
    sprite->inicializarTextura(path, sf::Vector2u(1, 1));
}

PlanoDeFundo::~PlanoDeFundo() {
}

void PlanoDeFundo::inicializaSprite() {
}

void PlanoDeFundo::renderiza() {
    sprite->atualiza(0, 0, false, posicao);
    sprite->renderiza();
}
