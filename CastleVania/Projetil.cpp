#include "Projetil.hpp"

const float Projetil::maxTempoAtivo = 5.0;

Projetil::Projetil(ID::ids id, sf::Vector2f pos, sf::Vector2f hit, int dano) :
Entidade(id, pos, hit),
Dano(dano),
tempoAtivo(0.0) { }

Projetil::~Projetil() { }

void Projetil::atira(sf::Vector2f pos, sf::Vector2f velo) {
    setVelocidade(velo);
    mudarPosicao(pos);
    tempoAtivo = 0.0;
    setAparece(true);
    if (velo.x < 0)
        setOlhandoEsquerda(true);
    else
        setOlhandoEsquerda(false);
}

void Projetil::atualizaAtivo(float dt) {
    tempoAtivo += dt;
    if (tempoAtivo > maxTempoAtivo)
        setAparece(false);
}

int Projetil::getDano() const {
    return Dano;
}
