#pragma once

#include "EntidadeLista.hpp"
#include "GerenciadorEvento.hpp"
#include "GerenciadorGrafico.hpp"
#include "GerenciadorInput.hpp"
#include "PontuacaoState.hpp"
#include "CarregaJogoState.hpp"
#include "AcabarJogoState.hpp"
#include "MenuPrincipalState.hpp"
#include "ControleMenu.hpp"
#include "NovoJogoState.hpp"
#include "NovoJogoState.hpp"
#include "MenuPausaState.hpp"
#include "JogandoJogoState.hpp"
#include "GerenciadorEstado.hpp"

#include <SFML/Graphics.hpp>

namespace GE {

    class Jogo : public GerenciadorEstado
    {
        private:

            GerenciadorGrafico* pGrafico;
            GerenciadorEvento* pEvento;
            GerenciadorInput* pInput;
            Nivel* pNivel;
            Jogador* jogador1;
            Jogador* jogador2;
            int nivelAtual;
            sf::Clock time;
            bool nivelAcabou;

            public:
            Jogo();
            ~Jogo();

            void iniciarEstados();

            void Executar();
            void save();

            Nivel* getpNivel() const;
            void setNivel(Nivel* pNivel);

            Jogador* getJogador1();
            Jogador* getJogador2();
            bool doisJogadoresAtivos() const;

            int getNivelAtual() const;
            void setNivelAtual(int num);

            void acabarJogo();
            void deleteNivel();
            void resetJogadores();
            bool taJogando() const;
            void setNivelAcabou(bool x);
    };
}
