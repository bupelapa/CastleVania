#include "Entidade.hpp"
#include "Animacao.hpp"



Entidade::Entidade(ID::ids id, sf::Vector2f pos, sf::Vector2f hit) :
Ent(id, pos) {
    hitbox = hit;
    velocidade = sf::Vector2f(0.0f, 0.0f);
    aparece = true;
    olhaEsquerda = false;
}

Entidade::Entidade() {
    hitbox = sf::Vector2f(0.0f, 0.0f);
    velocidade = sf::Vector2f(0.0f, 0.0f);
    aparece = false;
    olhaEsquerda = false;
}

Entidade::~Entidade() {
}

void Entidade::mudarPosicao(const Vector2f pos) {
    mudarPos(pos);
}

Vector2f Entidade::getPosicao() const {
    return getPos();
}

void Entidade::setVelocidade(const Vector2f vel) {
    velocidade = vel;
}

Vector2f Entidade::getVelocidade() const {
    return velocidade;
}

void Entidade::setHitbox(const Vector2f hit) {
    hitbox = hit;
}

Vector2f Entidade::getHitbox() const {
    return hitbox;
}

ID::ids Entidade::getId() const {
    return getID();
}

void Entidade::Mover(sf::Vector2f vec) {
    moverCorpo(vec);
}
