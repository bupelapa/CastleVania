#pragma once

#include "ConstrutorNivel.hpp"
#include "Estado.hpp"

class GerenciadorInput;

#define BACKGROUND_PATH "./imagens/planodefundo.png"

namespace GE {

class Jogo;

class CarregaJogoState : public Estado {
private:
    Jogo* pJogo;

public:
    CarregaJogoState(GerenciadorInput* GI = NULL, Jogo* pJ = NULL);
    ~CarregaJogoState();

    void atualiza(float dt);
    void renderiza();
    void resetEstado();
};

}
