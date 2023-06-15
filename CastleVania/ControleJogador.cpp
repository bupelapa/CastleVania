#include "ControleJogador.hpp"

#include "Jogador.hpp"

ControleJogador::ControleJogador(GerenciadorInput* pGI, Jogador* pP) :
Observador(pGI),
pJogador(pP),
pula(sf::Keyboard::W),
esquerda(sf::Keyboard::A),
direita(sf::Keyboard::D),
ataca(sf::Keyboard::Space) { }

ControleJogador::~ControleJogador() {
    pJogador = NULL;
}

void ControleJogador::notifica() {
    if (pJogador == NULL) {
        cout << "ERROR pointer para jogador NULL em ControleJogador::notifica()." << endl;
        exit(7);
    }
    if (sf::Keyboard::isKeyPressed(ataca))
        pJogador->setTaAtacando(true);

    if (sf::Keyboard::isKeyPressed(pula))
        pJogador->pula();

    if (sf::Keyboard::isKeyPressed(esquerda))
        pJogador->anda(true);

    if (sf::Keyboard::isKeyPressed(direita))
        pJogador->anda(false);

    if (!sf::Keyboard::isKeyPressed(esquerda) && !sf::Keyboard::isKeyPressed(direita))
        pJogador->setTaAndando(false);
}

void ControleJogador::addJogador(Jogador* p) {
    pJogador = p;
}

void ControleJogador::setKeys(sf::Keyboard::Key pula, sf::Keyboard::Key esquerda, sf::Keyboard::Key direita, sf::Keyboard::Key ataca) {
    this->pula = pula;
    this->esquerda = esquerda;
    this->direita = direita;
    this->ataca = ataca;
}
