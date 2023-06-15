#pragma once

#include "Menu.hpp"
#include "Estado.hpp"

class GerenciadorInput;

#define BACKGROUND_MAIN_MENU "./imagens/menuprincipal.png"

namespace GE {

class Jogo;

class MenuPrincipalState : public Menu, public Estado {
private:
    Jogo* pJogo;

public:
    MenuPrincipalState(GerenciadorInput* GI = NULL, Jogo* pJ = NULL);
    ~MenuPrincipalState();

    void atualiza(float dt);
    void renderiza();
    void resetEstado();
    void exec();
};

}

