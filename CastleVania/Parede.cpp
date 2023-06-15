#include "Parede.hpp"
#include "Animacao.hpp"
#include "GerenciadorGrafico.hpp"

#include "string.h"

Parede::Parede(sf::Vector2f pos, int tipoParede, bool olhandoEsquerda) :
Obstaculo(pos, sf::Vector2f(WALL_WIDTH, WALL_HEIGHT),0, ID::parede),
tipoParede(tipoParede) {
    setOlhandoEsquerda(olhandoEsquerda);
    inicializaSprite();
}

Parede::~Parede() {
}

void Parede::atualiza(float dt) {
    sprite->atualiza(0, dt, olhandoEsquerda(), posicao);
}

void Parede::save() {
    if (getAparece()) {
        ofstream file;
        file.open("./Saves/Parede.txt", ios::app);
        if (!file) {
            cout << "ERROR CARREGAR PAREDES" << endl;
            abort();
        }
        file << getPosicao().x << ' ' << getPosicao().y << ' ' << olhandoEsquerda() << ' ' << tipoParede << endl;
        file.close();
    }
}

void Parede::inicializaSprite() {
    if (tipoParede == 1)
        sprite->inicializarTextura(PAREDE_PATH_TERRA, sf::Vector2u(1, 1));
    else if (tipoParede == 2)
        sprite->inicializarTextura(PAREDE_PATH_TIJOLO, sf::Vector2u(1, 1));
    else
        sprite->inicializarTextura(PAREDE_PATH_TIJOLO, sf::Vector2u(1, 1));
}

