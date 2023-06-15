#pragma once

#include "Obstaculo.hpp"

#define PLATAFORMA_PATH_TERRA "./imagens/chaoprimeirafase.png"
#define PLATAFORMA_PATH_TIJOLO "./imagens/chaosegundafase.png"
#define PLATAFORMA_PATH_RETO "./imagens/chaoprimeirafase.png"



class GerenciadorGrafico;

class Plataforma : public Obstaculo {
private:
    int platTipo;

public:
    Plataforma(sf::Vector2f pos, int platTipo = 1);
    ~Plataforma();
    void atualiza(float dt);
    void inicializaSprite();
    void save();
};

