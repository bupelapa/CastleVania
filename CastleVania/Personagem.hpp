#pragma once

#include "Entidade.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
class Animacao;
class GerenciadorGrafico;


        class Personagem : public Entidade {
        protected:
           int vida;
           int dano;
           bool taAtacando;
            virtual void inicializaSprite() = 0;
            virtual void atualiza (float dt) = 0;
        public:
            Personagem(ID::ids id, sf::Vector2f pos, sf::Vector2f hit, int vd, int auxdano);
            ~Personagem();

            int ataca();
            void tomaDano(int auxdano);

            void setTaAtacando(const bool val = false) { taAtacando = val; }
            bool getTaAtacando() const { return taAtacando; }

            virtual void save() = 0;
            void setVida(int vd) { vida = vd; }
            int getVida() const;
            virtual void atualizaSprite(float dt) = 0;
        };
