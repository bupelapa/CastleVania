#include "Ghoul.hpp"
#include "Animacao.hpp"

const float Ghoul::tempoAtaque = 1;

Ghoul::Ghoul(sf::Vector2f pos, Jogador* pJogador1, Jogador* pJogador2) :
Inimigo(ID::ghoul, pos, sf::Vector2f(GHOUL_LARGURA, GHOUL_ALTURA), GHOUL_VIDA, GHOUL_DANO, pJogador1, pJogador2) {
    inicializaSprite();
}

Ghoul::~Ghoul() {
}

void Ghoul::inicializaSprite() {
    sprite->inicializarTextura(GHOUL_PATH, sf::Vector2u(8, 1));
}

void Ghoul::atualiza(float dt) {
    if (vida <= 0) {
        setAparece(false);
        return;
    }

    velocidade = Vector2f(velocidade.x, velocidade.y + GRAVIDADE * dt);

    if (velocidade.y > 700)
        velocidade = Vector2f(velocidade.x, 700);

    mudarPosicao(Vector2f(velocidade.x * dt + posicao.x, velocidade.y * dt + posicao.y));
    comportamentoGhoul();
    atualizaSprite(dt);

    /* Ataca se possivel */
    ataqueTempoDeEspera += dt;
    if (ataqueTempoDeEspera >= tempoAtaque * 3) {
        if (abs(getJogadorProximo()->getPosicao().x - posicao.x) <= GHOUL_ATAQUEX)
            ataca();
    }
}
void Ghoul::comportamentoGhoul() {
    float dx = getJogadorProximo()->getPosicao().x - posicao.x;
    if (abs(dx) < GHOUL_MOTIONX_MAX && abs(dx) > GHOUL_MOTIONX_MIN) {
        if (dx > 0) {
            setVelocidade(sf::Vector2f(GHOUL_VELOCIDADEX, getVelocidade().y));
            setOlhandoEsquerda(false);
        } else {
            setVelocidade(sf::Vector2f(-GHOUL_VELOCIDADEX, getVelocidade().y));
            setOlhandoEsquerda(true);
        }
    } else {
        setVelocidade(sf::Vector2f(0, getVelocidade().y));
    }
}

void Ghoul::save() {
    if (getAparece()) {
        ofstream file;
        file.open("./Saves/Ghoul.txt", ios::app);
        if (!file) {
            cout << "ERRO CARREGANDO GHOUL" << endl;
            abort();
        }
        file << getPosicao().x << ' ' << getPosicao().y - 50 << ' ' << getVelocidade().x << ' ' << getVelocidade().y << ' ' << getVida() << ' ' << olhandoEsquerda() << endl;
        file.close();
    }
}

void Ghoul::atualizaSprite(float dt) {
    /* Atacando */
    if (taAtacando && tempoAtacando <= tempoAtaque) {
        tempoAtacando += dt;
            sprite->atualiza(0, dt, olhandoEsquerda(), posicao);
    }
    /* Andando */
    else if (abs(velocidade.x) > 0.001)
        sprite->atualiza(0, dt, olhandoEsquerda(), posicao);
    /* Idle */
    else
        sprite->atualiza(0, dt, olhandoEsquerda(), posicao);
}

void Ghoul::ataca() {
    int dx = getJogadorProximo()->getPosicao().x - posicao.x;
    if (abs(dx) <= GHOUL_ATAQUEX) {
        if (olhandoEsquerda() && dx < 0)
            getJogadorProximo()->tomaDano(GHOUL_DANO);
        else if (!olhandoEsquerda() && dx > 0)
            getJogadorProximo()->tomaDano(GHOUL_DANO);
        setTaAtacando(true);
        ataqueTempoDeEspera = 0;
        tempoAtacando = 0;
    }
}
