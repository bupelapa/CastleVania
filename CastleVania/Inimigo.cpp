#include "Inimigo.hpp"

#include "Animacao.hpp"
#include "Jogador.hpp"
#include "math.h"

Inimigo::Inimigo(ID::ids id, sf::Vector2f pos, sf::Vector2f hit, int vd, int dn, Jogador* pJogador1, Jogador* pJogador2) :
Personagem(id, pos, hit, vd, dn),
pJogador1(pJogador1),
pJogador2(pJogador2),
ataqueTempoDeEspera(0.0) {
    tempoTotalAtaque = 0.0f;
}

Inimigo::~Inimigo() {
}

Jogador* Inimigo::getJogadorProximo() {
    int x1, x2;
    if (pJogador2) {
        x1 = abs(pJogador1->getPosicao().x - posicao.x);
        x2 = abs(pJogador2->getPosicao().x - posicao.x);
        if (x1 < x2)
            return pJogador1;
        else
            return pJogador2;
    }
    else
        return pJogador1;
}





