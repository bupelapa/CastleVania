#pragma once

#include "Personagem.hpp"
#include "ControleJogador.hpp"
#include <math.h>

#define JOGADOR_1_PATH "./imagens/jogador1.png"
#define JOGADOR_2_PATH "./imagens/jogador2.png"

#define JOGADOR_VELOCIDADE 600.f
#define PULA_VELOCIDADE 3000.f
#define JOGADOR_VIDA 10000
#define JOGADOR_DANO 25
#define JOGADOR_LARGURA 95
#define JOGADOR_ALTURA 80
#define JOGADOR_PULA 220
#define JOGADOR_ATACA 200

class Animacao;
class GerenciadorInput;




            class Jogador : public Personagem {
            private:
                bool podePular;
                bool primeiroAtaque;
                float tempoTotalAteAtaque;
                static const float tempoDeAtaque;
                bool taAndando;
                const bool Jogador1;
                ControleJogador pc;
                int pontos;
            public:
            Jogador(const bool eJogador1 = true, GerenciadorInput* pGI = NULL);
            ~Jogador();

            void atualiza(float dt);
            void colisao(Entidade* outro, sf::Vector2f vetorColisao = sf::Vector2f(0.0f, 0.0f));
            void setPulo(const bool val = true) { podePular = val; }
            void inicializaSprite();
            int podeAtacar(float dt = 0.0f);
            void anda(bool left);
            void pula();
            void setTaAndando(const bool val) { taAndando = val; }
            void atualizaSprite(float dt);
            const bool eJogador1() const { return Jogador1; }
            void reset();
            void save();
            int getPontos() { return pontos; }
            void setPontos(int pt) { pontos = pt; }
            void operator+=(int pt);

            };


