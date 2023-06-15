#pragma once
#include "stdafx.h"
#include "Entidade.hpp"

class Projetil : public Entidade{
protected:
    int Dano;
    float tempoAtivo;
    static const float maxTempoAtivo;

public:
    Projetil(ID::ids id, sf::Vector2f pos, sf::Vector2f hit, int dano);
    virtual ~Projetil();
    void atira(sf::Vector2f pos, sf::Vector2f velo);
    void atualizaAtivo(float dt);
    int getDano() const;
};
