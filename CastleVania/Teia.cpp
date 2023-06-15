#include "Teia.hpp"
#include "Animacao.hpp"
#include "GerenciadorGrafico.hpp"

Teia::Teia(sf::Vector2f pos) :
Obstaculo(pos, sf::Vector2f(TEIA_LARGURA, TEIA_ALTURA),2, ID::teia) {
    sprite->inicializarTextura(TEIA_PATH, sf::Vector2u(1, 1));
}

Teia::~Teia() {
}

void Teia::atualiza(float dt) {
    sprite->atualiza(0, dt, olhandoEsquerda(), posicao);
}

void Teia::save() {
    if (getAparece()) {
        ofstream file;
        file.open("./Saves/Teia.txt", ios::app);
        if (!file) {
            cout << "ERRO CARREGANDO TEIA" << endl;
            abort();
        }
        file << getPosicao().x << ' ' << getPosicao().y << endl;
        file.close();
    }
}
