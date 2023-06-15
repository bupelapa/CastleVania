#include "Mago.hpp"

#include "Animacao.hpp"
#include <math.h>

const float Mago::tempoAtaque = 0.4;

Mago::Mago(sf::Vector2f pos, BolaDeFogo* bfogo, Jogador* pJogador1, Jogador* pJogador2, int minH, int maxH) :
Inimigo(ID::mago, pos, sf::Vector2f(MAGO_LARGURA, MAGO_ALTURA), MAGO_VIDA, MAGO_DANO, pJogador1, pJogador2),
boladefogo(bfogo) {

    inicializaSprite();
    setVelocidade(sf::Vector2f(0, MAGO_VELOCIDADE));

    if (minH == 0)
        minHeight = int(pos.y);
    else
        minHeight = minH;

    if (maxH == 0)
        maxHeight = int(pos.y - MAX_VAR_ALTURA);
    else
        maxHeight = maxH;
}

Mago::~Mago() {
}

void Mago::inicializaSprite() {
    sprite->inicializarTextura(Mago_PATH, sf::Vector2u(4, 5));
}

void Mago::atualiza(float dt) {
    /* checa se morreu */
    if (vida <= 0) {
        setAparece(false);
        boladefogo->setAparece(false);
    }
    /* Movimento em y  */
    if ((posicao.y > minHeight) && velocidade.y > 0)
        velocidade.y *= -1;
    else if ((posicao.y < maxHeight) && velocidade.y < 0)
        velocidade.y *= -1;

    mudarPosicao(Vector2f(posicao.x, velocidade.y * dt + posicao.y));

    atualizaSprite(dt);

    /* Ataca se possivel */
    ataqueTempoDeEspera += dt;
    if (ataqueTempoDeEspera >= tempoAtaque * 5 && !boladefogo->getAparece() && getAparece()) {
        if (abs(getJogadorProximo()->getPosicao().x - posicao.x) <= MAGO_ATAQUEX) {
            taAtacando = true;
            if (getJogadorProximo()->getPosicao().x - posicao.x > 0) {
                setOlhandoEsquerda(true);
            } else
                setOlhandoEsquerda(false);
            ataqueTempoDeEspera = 0;
        }
    }
}

/* Joga bola de fogo na direção do jogador*/
void Mago::ataca() {
    Jogador* pJogador = getJogadorProximo();
    int deltax, deltay;
    deltax = abs(pJogador->getPosicao().x - posicao.x);
    deltay = abs(pJogador->getPosicao().y - posicao.y);
    float teta = atan2f(deltax, deltay);

    float vx, vy;
    vx = MAGO_BOLADEFOGO_VELOCIDADE * sin(teta);
    vy = MAGO_BOLADEFOGO_VELOCIDADE * cos(teta);

    if (olhandoEsquerda()) {
        boladefogo->atira(getPosicao() + sf::Vector2f(MAGO_LARGURA, 0), sf::Vector2f(vx, vy));
    } else {
        boladefogo->atira(getPosicao() - sf::Vector2f(MAGO_LARGURA, 0), sf::Vector2f(-vx, vy));
    }
    setTaAtacando(false);
    tempoTotalAtaque = 0;

}

/* Salva mago e bola de fogo. */
void Mago::save() {
    if (getAparece()) {
        ofstream file;
        file.open("./Saves/Mago.txt", ios::app);
        if (!file) {
            cout << "ERRO CARREGAR MAGO" << endl;
            abort();
        }
        file << getPosicao().x << ' '
             << getPosicao().y << ' '
             << getVelocidade().x << ' '
             << getVelocidade().y << ' '
             << boladefogo->getPosicao().x << ' '
             << boladefogo->getPosicao().y << ' '
             << boladefogo->getVelocidade().x << ' '
             << boladefogo->getVelocidade().y << ' '
             << boladefogo->getAparece() << ' '
             << getVida() << ' '
             << olhandoEsquerda() << ' '
             << minHeight << ' '
             << maxHeight << endl;
        file.close();
    }
}

void Mago::atualizaSprite(float dt) {
    if (taAtacando) {
        tempoTotalAtaque += dt;
        if (tempoTotalAtaque < tempoAtaque)
            sprite->atualiza(2, dt, olhandoEsquerda(), posicao);
        else

            ataca();

    } else
        sprite->atualiza(0, dt, olhandoEsquerda(), posicao);
}
