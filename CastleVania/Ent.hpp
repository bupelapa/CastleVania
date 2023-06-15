#pragma once

#include "Id.hpp"
#include "stdafx.h"



class Animacao;

class Ent {
protected:
    Animacao* sprite;
    ID::ids id;  // provavelmente terá que ser um const
    sf::Vector2f posicao;

public:
    Ent(ID::ids id,sf::Vector2f pos);
    Ent();
    virtual ~Ent();

    void mudarPos(const sf::Vector2f pos);
    sf::Vector2f getPos() const;
    void moverCorpo(const sf::Vector2f vec);
    ID::ids getID() const;

    virtual void inicializaSprite() = 0;
    virtual void atualiza(float dt) = 0;
    virtual void renderiza();
};

