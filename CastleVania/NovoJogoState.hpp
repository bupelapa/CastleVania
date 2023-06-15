#pragma once

#include "Menu.hpp"
#include "Estado.hpp"
#include "ConstrutorNivel.hpp"
class GerenciadorInput;

#define BACKGROUND_MAIN_MENU "./imagens/menuprincipal.png"

namespace GE {

class Jogo;

class NovoJogoState : public Menu, public Estado {
private:
    Jogo* pJogo;

public:
    NovoJogoState(GerenciadorInput* GI = NULL, Jogo* pJ = NULL);
    ~NovoJogoState();

    void atualiza(float dt);
    void renderiza();
    void resetEstado();
    void exec();
    void comecaNovoNivel(bool eUmJogador);
};

}

