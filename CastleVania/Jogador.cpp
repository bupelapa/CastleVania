#include "Jogador.hpp"
#include "Animacao.hpp"
#include "GerenciadorEvento.hpp"
#include <math.h>




const float Jogador::tempoDeAtaque = 0.65;

Jogador::Jogador(const bool eJogador1, GerenciadorInput* pGI) :
Personagem(ID::jogador, sf::Vector2f(0, 0), sf::Vector2f(JOGADOR_LARGURA, JOGADOR_ALTURA), JOGADOR_VIDA, JOGADOR_DANO),
Jogador1(eJogador1),
pc(pGI, this),
pontos(0) {
    taAndando = false;
    tempoTotalAteAtaque = 0.0f;
    primeiroAtaque = true;
    podePular = true;
    inicializaSprite();
}

Jogador::~Jogador() {
}

/* Atualiza posicao e velocidade do Jogador */
void Jogador::atualiza(float dt) {
    if (vida <= 0)
        setAparece(false);

    if (taAndando)
        velocidade = Vector2f(velocidade.x, velocidade.y + GRAVIDADE * dt);
    else
        velocidade = Vector2f(velocidade.x * 0.01f, velocidade.y + GRAVIDADE * dt);

    if (velocidade.y > 700)
        velocidade = Vector2f(velocidade.x, 700);

    mudarPosicao(Vector2f(velocidade.x * dt + posicao.x, velocidade.y * dt + posicao.y));

    atualizaSprite(dt);
}

/* Inicializa as animacoes */
void Jogador::inicializaSprite() {
    if (Jogador1)
        sprite->inicializarTextura(JOGADOR_1_PATH, sf::Vector2u(4, 6));
    else {
        sprite->inicializarTextura(JOGADOR_2_PATH, sf::Vector2u(4, 6));
        pc.setKeys(sf::Keyboard::Up, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::RControl);
    }
}

/* Retorna a fila de animacao de ataque do personagem */
int Jogador::podeAtacar(float dt) {
    if (taAtacando) {
        tempoTotalAteAtaque += dt;
        if (tempoTotalAteAtaque < tempoDeAtaque) {
            return 4;
        } else {
            primeiroAtaque = !primeiroAtaque;
            tempoTotalAteAtaque = 0;
        }

        taAtacando = false;
    }
    return 0;
}

/* Anda para esquerda < TRUE
  Anda para direita = FALSE */
void Jogador::anda(bool esquerda) {
    taAndando = true;
    if (esquerda)
        velocidade = Vector2f(-JOGADOR_VELOCIDADE, velocidade.y);
    else
        velocidade = Vector2f(JOGADOR_VELOCIDADE, velocidade.y);

    setOlhandoEsquerda(esquerda);
}

/* faz o Jogador pular */
void Jogador::pula() {
    if (podePular) {
        velocidade = Vector2f(velocidade.x, -sqrtf(2.0f * GRAVIDADE * JOGADOR_PULA));
        podePular = false;
    }
}


/* atualiza a animacao */
void Jogador::atualizaSprite(float dt) {
    /* Atacando */
    if (podeAtacar() != 0)
        sprite->atualiza(podeAtacar(dt), dt, olhandoEsquerda(), posicao);
    /* Caindo */
    else if (velocidade.y > 150)
        sprite->atualiza(3, dt, olhandoEsquerda(), posicao);
    /* Pulando */
    else if (velocidade.y < -100 && !podePular)
        sprite->atualiza(2, dt, olhandoEsquerda(), posicao);
    /* Andando */
    else if (abs(velocidade.x) > 0.001)
        sprite->atualiza(1, dt, olhandoEsquerda(), posicao);
    /* Idle */
    else
        sprite->atualiza(0, dt, olhandoEsquerda(), posicao);
}

void Jogador::reset() {
    taAndando = false;
    tempoTotalAteAtaque = 0.0f;
    primeiroAtaque = true;
    podePular = true;
    vida = JOGADOR_VIDA;
    setAparece(true);
    setVelocidade(sf::Vector2f(0.0f, 0.0f));
    inicializaSprite();
}

/* funcao para salvar os dados do jogador em txt */
void Jogador::save() {
    ofstream file;
    if (eJogador1()) {
        file.open("./Saves/Jogador1.txt");
        if (!file) {
            cout << "ERRO CARREGANDO JOGADOR" << endl;
            abort();
        }
        file << getPosicao().x << ' ' << getPosicao().y - 30 << ' ' << getVelocidade().x << ' ' << (int) getVelocidade().y << ' ' << getVida() << ' ' << pontos << ' ' << olhandoEsquerda() << endl;
        file.close();
    } else {
        file.open("./Saves/Jogador2.txt");
        if (!file) {
            cout << "ERRO CARREGANDO JOGADOR" << endl;
            abort();
        }
        file << getPosicao().x << ' ' << getPosicao().y - 30 << ' ' << getVelocidade().x << ' ' << (int) getVelocidade().y << ' ' << getVida() << ' ' << pontos << ' ' << olhandoEsquerda() << endl;
        file.close();
    }
}

void Jogador::operator+=(int pt) {
    pontos += pt;
}
