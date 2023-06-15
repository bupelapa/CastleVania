#pragma once

#include "Obstaculo.hpp"

#define ESPINHO_PATH "./imagens/Espinho.png"

#define ESPINHO_DANO 5
#define ESPINHO_LARGURA 225
#define ESPINHO_ALTURA 45

class Espinho : public Obstaculo {
public:
    Espinho(sf::Vector2f pos);
    ~Espinho();
    void atualiza(float dt);
    void inicializaSprite() { }
    void save();
};
