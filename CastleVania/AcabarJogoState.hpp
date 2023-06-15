#pragma once

#include "Menu.hpp"
#include "Estado.hpp"

class GerenciadorInput;
class Nivel;
class GerenciadorGrafico;

#define LEADERBOARD_TXT_PATH "./Saves/Placar.txt"
#define TEXT_SIZE 24

namespace GE {

class Jogo;

class AcabarJogoState : public Menu, public Estado {
private:
    Jogo* pJogo;
    sf::Text texto;
    sf::Text textoFimDeJogo;
    GerenciadorGrafico* GG;
    GerenciadorInput* pGI;

    char nomeJ[30];
    sf::String apelido;

public:
    AcabarJogoState(GerenciadorInput* GI = NULL, Jogo* pJ = NULL);
    ~AcabarJogoState();

    void atualiza(float dt);
    void renderiza();
    void resetEstado();
    void exec();
    void salvaPontos();
    void atualizaNome();
    int getPontos();
};

}

