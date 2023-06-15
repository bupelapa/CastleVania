#include "Plataforma.hpp"
#include "Animacao.hpp"
#include "GerenciadorGrafico.hpp"
#include <string.h>

Plataforma::Plataforma(sf::Vector2f pos, int platTipo) :
   Obstaculo(pos, sf::Vector2f(PLATAFORMA_LARGURA, PLATAFORMA_ALTURA),0, ID::plataforma),
platTipo(platTipo) {
    inicializaSprite();
}

Plataforma::~Plataforma() { }

void Plataforma::atualiza(float dt) {
    sprite->atualiza(0, dt, false, posicao);
}

void Plataforma::inicializaSprite() {
    if (platTipo == 1)
        sprite->inicializarTextura(PLATAFORMA_PATH_TERRA, sf::Vector2u(1, 1));
    else if (platTipo == 2)
        sprite->inicializarTextura(PLATAFORMA_PATH_TIJOLO, sf::Vector2u(1, 1));
    else
        sprite->inicializarTextura(PLATAFORMA_PATH_RETO, sf::Vector2u(1, 1));
}

void Plataforma::save() {
    if (getAparece()) {
        ofstream file;
        file.open("./Saves/Plataforma.txt", ios::app);
        if (!file) {
            cout << "Error abrindo save plataforma" << endl;
            abort();
        }
        file << getPosicao().x << ' ' << getPosicao().y << " " << platTipo << endl;
        file.close();
    }
}
