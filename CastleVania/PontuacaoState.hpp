#pragma once

#include "Menu.hpp"
#include "Estado.hpp"
#include <vector>

class GerenciadorInput;
class GerenciadorGrafico;

#define PLANODEFUNDO_PRINCIPAL "./imagens/planodefundo.png"
#define LEADERBOARD_TXT_PATH "./Saves/Placar.txt"
#define TEXT_SIZE 24

namespace GE {

class Jogo;

class PontuacaoState : public Menu, public Estado {
private:
    Jogo* pJogo;
    std::vector<sf::Text*> vectorOfTexts;
    std::vector<sf::Text*>::iterator itr;
    GerenciadorGrafico* GG;

public:
    PontuacaoState(GerenciadorInput* GI = NULL, Jogo* pJ = NULL);
    ~PontuacaoState();

    void atualiza(float dt);
    void renderiza();
    void resetEstado();
    void exec();
};

}

