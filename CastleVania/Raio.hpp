#pragma once
#include "Projetil.hpp"

class Animacao;

#define PATH_RAIO_TEXTURA "./imagens/raio.png"

#define RAIO_LARGURA 40
#define RAIO_ALTURA 30
#define RAIO_VELOCIDADE 800

#define RAIO_DANO 100

class Raio : public Projetil {
public:
    Raio(sf::Vector2f pos);
    ~Raio();
    void atualiza(float dt);
    void inicializaSprite();
    void save() { }
};


