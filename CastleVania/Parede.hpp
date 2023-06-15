#pragma once

#include "Obstaculo.hpp"
#include "stdafx.h"

#define PAREDE_PATH_TERRA "./imagens/ParedeTerra.png"
#define PAREDE_PATH_TIJOLO "./imagens/ParedeTijolo.png"


#define WALL_HEIGHT 45
#define WALL_WIDTH 45

class Animacao;
class GerenciadorGrafico;
class Parede : public Obstaculo {
private:
    int tipoParede;

public:
    Parede(sf::Vector2f pos, int tipoParede = 1, bool olhandoEsquerda = false);
    ~Parede();
    void atualiza(float dt);
    void inicializaSprite();
    void save();
};
