#include "Boss.hpp"
#include "Animacao.hpp"

const float Boss::tempoAtaque = 0.7;

Boss::Boss(sf::Vector2f pos, Raio* pRaio, Jogador* pJogador1, Jogador* pJogador2, int minH, int maxH, int minD, int maxD) :
Inimigo(ID::boss, pos, sf::Vector2f(BOSS_LARGURA, BOSS_ALTURA), BOSS_VIDA, BOSS_DANO, pJogador1, pJogador2),
raio(pRaio) {
    inicializaSprite();
    setVelocidade(sf::Vector2f(BOSS_VELOCIDADE, BOSS_VELOCIDADE));

    if (minH == 0)
        minHeight = int(pos.y);
    else
        minHeight = minH;

    if (maxH == 0)
        maxHeight = int(pos.y - MAX_VAR_ALTURA_BOSS);
    else
        maxHeight = maxH;

    if (minD == 0)
        minDistance = int(pos.x);
    else
        minDistance = minD;

    if (maxD == 0)
        maxDistance = int(pos.x - MAX_VAR_DISTANCIA_BOSS);
    else
        maxDistance = maxD;
}

Boss::~Boss() {
}

void Boss::inicializaSprite() {
    sprite->inicializarTextura(BOSS_PATH, sf::Vector2u(8, 3));
}

void Boss::atualiza(float dt) {
    /* checa se morreu */
    if (vida <= 0) {
        setAparece(false);
        raio->setAparece(false);
    }
    if (getJogadorProximo()->getPosicao().x - posicao.x > 0)
        velocidade.x = BOSS_VELOCIDADE;
    else
        velocidade.x = -BOSS_VELOCIDADE;

    if ((posicao.y > minHeight) && velocidade.y > 0)
        velocidade.y *= -1;
    else if ((posicao.y <= maxHeight) && velocidade.y < 0)
        velocidade.y *= -1;


    mudarPosicao(Vector2f(velocidade.x * dt + posicao.x, velocidade.y * dt + posicao.y));
    atualizaSprite(dt);

    /* Ataca se possivel */
    ataqueTempoDeEspera += dt;
    if (ataqueTempoDeEspera >= tempoAtaque  && !raio->getAparece() && getAparece()) {
        if (abs(getJogadorProximo()->getPosicao().x - posicao.x) <= BOSS_ATAQUEX) {
            taAtacando = true;
            if (getJogadorProximo()->getPosicao().x - posicao.x > 0) {
                setOlhandoEsquerda(false);
            } else
                setOlhandoEsquerda(true);
            ataqueTempoDeEspera = 0;
        }
    }
}


void Boss::save() {
    if (getAparece()) {
        ofstream file;
        file.open("./Saves/Boss.txt", ios::app);
        if (!file) {
            cout << "ERRO CARREGANDO BOSS" << endl;
            abort();
        }
        file << getPosicao().x << ' '
             << getPosicao().y << ' '
             << getVelocidade().x << ' '
             << getVelocidade().y << ' '
             << raio->getPosicao().x << ' '
             << raio->getPosicao().y << ' '
             << raio->getVelocidade().x << ' '
             << raio->getVelocidade().y << ' '
             << raio->getAparece() << ' '
             << getVida() << ' '
             << olhandoEsquerda() << ' '
             << minHeight << ' '
             << maxHeight << ' '
             << minDistance << ' '
             << maxDistance << endl;

            file.close();
    }
}

void Boss::atualizaSprite(float dt) {
    /* Atacando */
    if (taAtacando) {
        tempoTotalAtaque += dt;
        if (tempoTotalAtaque < tempoAtaque)
            sprite->atualiza(1, dt, olhandoEsquerda(), posicao);
        else
            ataca();
    }
    //Idle
      else
        sprite->atualiza(0, dt, olhandoEsquerda(), posicao);
}

void Boss::ataca() {
    Jogador* pJogador = getJogadorProximo();
    int deltax, deltay;
    deltax = abs(pJogador->getPosicao().x - posicao.x);
    deltay = abs(pJogador->getPosicao().y - posicao.y);
    float teta = atan2f(deltax, deltay);

    float vx, vy;
    vx = BOSS_RAIO_VELOCIDADE * sin(teta);
    vy = BOSS_RAIO_VELOCIDADE * cos(teta);

    if (olhandoEsquerda()) {
        raio->atira(getPosicao() - sf::Vector2f(BOSS_LARGURA, 0), sf::Vector2f(-vx, vy));
    } else {
        raio->atira(getPosicao() + sf::Vector2f(BOSS_LARGURA, 0), sf::Vector2f(vx, vy));
    }
    setTaAtacando(false);
    tempoTotalAtaque = 0;
    }

