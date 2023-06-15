#pragma once

#include "Ent.hpp"
#include "Id.hpp"
#include "stdafx.h"

class Animacao;
class GerenciadorGrafico;

using namespace sf;

class Entidade : public Ent {
private:
    bool aparece;
    bool olhaEsquerda;

protected:
    sf::Vector2f velocidade;
    sf::Vector2f hitbox;

public:
    Entidade(ID::ids id, sf::Vector2f pos, sf::Vector2f hit);
    Entidade();
    virtual ~Entidade();

    void mudarPosicao(const sf::Vector2f pos);
    Vector2f getPosicao() const;

    void setVelocidade(const Vector2f vel);
    Vector2f getVelocidade() const;

    void setHitbox(const Vector2f hit);
    Vector2f getHitbox() const;

    virtual void atualiza(float dt) = 0;
    virtual void inicializaSprite() = 0;

    ID::ids getId() const;
    void Mover(sf::Vector2f vec);

    void setAparece(const bool val = true) { aparece = val; }
    bool getAparece() { return aparece; }

    void setOlhandoEsquerda(bool olhandoEsquerda) { olhaEsquerda = olhandoEsquerda; }
    bool olhandoEsquerda() const { return olhaEsquerda; }
    virtual void save() = 0;
};

