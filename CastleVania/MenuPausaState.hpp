#pragma once

#include "Menu.hpp"
#include "Estado.hpp"

class GerenciadorInput;

#define BACKGROUND_PATH "./imagens/planodefundo.png"

namespace GE {

class Jogo;

class MenuPausaState : public Menu, public Estado {
private:
    Jogo* pJogo;

public:
    MenuPausaState(GerenciadorInput* GI = NULL, Jogo* pJ = NULL);
    ~MenuPausaState();

    void atualiza(float dt);
    void renderiza();
    void exec();
    void resetEstado();
};

}
