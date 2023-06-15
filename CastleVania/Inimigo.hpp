#pragma once

#include "Personagem.hpp"
#include "BolaDeFogo.hpp"
#include "Raio.hpp"


// usado p/ gerar números aleatórios
#include <time.h>

// utuliza a função fabs
#include <cmath>


class Animacao;
class Jogador;


            class Inimigo : public Personagem{
            protected:
                Jogador* pJogador1;
                Jogador* pJogador2;
                sf::Clock relogio;
                float tempoTotalAtaque;
                float ataqueTempoDeEspera;
            public:
                Inimigo(ID::ids id, sf::Vector2f pos, sf::Vector2f hit, int vd, int dn, Jogador* pJogador1 = NULL, Jogador* pJogador2 = NULL);
                ~Inimigo();
                virtual void atualiza(float dt) = 0;
                virtual void ataca() = 0;
                virtual void inicializaSprite() = 0;
                virtual void save() = 0;
                Jogador* getJogadorProximo();
            };


