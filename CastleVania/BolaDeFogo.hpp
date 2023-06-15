#pragma once
#include "Projetil.hpp"

class Animacao;

#define PATH_BOLADEFOGO_TEXTURA "./imagens/boladefogo.png"

#define BOLADEFOGO_LARGURA 120
#define BOLADEFOGO_ALTURA 72
#define BOLADEFOGO_VELOCIDADEX 500
#define BOLADEFOGO_HMAX 200
#define BOLADEFOGO_DANO 100

class BolaDeFogo : public Projetil {
public:
    BolaDeFogo(sf::Vector2f pos);
    ~BolaDeFogo();
    void atualiza(float dt);
    void inicializaSprite();
    void save() { }
};

