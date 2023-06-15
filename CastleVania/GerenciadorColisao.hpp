#pragma once

#include "EntidadeLista.hpp"
#include "stdafx.h"
#include <math.h>


        class GerenciadorColisao{
        private:
            EntidadeLista* list;

        public:
            GerenciadorColisao(EntidadeLista* pLista = NULL);
            ~GerenciadorColisao();
            void calculaColisao();
            void setLista(EntidadeLista* pLista) { list = pLista; }

            void andaX(Entidade* ent1, Entidade* ent2, float intersectaaX);
            void andaY(Entidade* ent1, Entidade* ent2, float intersectaY);
            void emCima(Entidade* ent1, Entidade* ent2, float intersectaX, float dx);
            void colidirJogador(Entidade* ent1, Entidade* ent2, float dx, float dy, float intersectaX, float intersectaY);
            void colidirInimigo(Entidade* ent1, Entidade* ent2, float dx, float dy, float intersectaX, float intersectaY);
            void colidirProjetil(Entidade* ent1, Entidade* ent2, float dx, float dy, float intersectaX, float intersectaY);
            void colidirPlataforma(Entidade* ent1, Entidade* ent2, float dx, float dy, float intersectaX, float intersectaY);
            void ataqueInimigo(Entidade* ent1, Entidade* ent2);
            void ataqueJogador(Entidade* ent1, Entidade* ent2, float dx, float dy);
        };

