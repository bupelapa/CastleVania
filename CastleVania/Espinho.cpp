#include "Espinho.hpp"

#include "Animacao.hpp"
#include "GerenciadorGrafico.hpp"

Espinho::Espinho(sf::Vector2f pos) :
    Obstaculo(pos, sf::Vector2f(ESPINHO_LARGURA, ESPINHO_ALTURA), ESPINHO_DANO,ID::espinho) {
    sprite->inicializarTextura(ESPINHO_PATH, sf::Vector2u(1, 1));
}

Espinho::~Espinho() {
}

void Espinho::atualiza(float dt) {
    dt /= 4;
    sprite->atualiza(0, dt, olhandoEsquerda(), posicao);
}

void Espinho::save() {
    if (getAparece()) {
        ofstream file;
        file.open("./Saves/Espinho.txt", ios::app);
        if (!file) {
            cout << "ERROR ABRINDO ESPINHO" << endl;
            abort();
        }
        file << getPosicao().x << ' ' << getPosicao().y << endl;
        file.close();
    }
}
