#pragma once

#include "Obstaculo.hpp"
#define TEIA_PATH "./imagens/teia.png"

class Teia : public Obstaculo {
public:
    Teia(sf::Vector2f pos);
    ~Teia();
    void atualiza(float dt);

    void inicializaSprite() { }
    void save();
};
