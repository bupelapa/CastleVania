#pragma once

#include "Entidade.hpp"

class Obstaculo : public Entidade {
protected:
    float efeito;

public:
    Obstaculo(sf::Vector2f pos, sf::Vector2f hit, int efet, ID::ids id);
    virtual ~Obstaculo() { }
    float getEfeito() const { return efeito; }
};
