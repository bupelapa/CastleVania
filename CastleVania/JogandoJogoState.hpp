#pragma once

#include "Estado.hpp"

class GerenciadorInput;
class Nivel;

namespace GE {

class Jogo;

class JogandoJogoState : public Estado {
private:
    Jogo* pJogo;
    Nivel* pNivel;

public:
    JogandoJogoState(GerenciadorInput* GI = NULL, Jogo* pJ = NULL);
    ~JogandoJogoState();

    void atualiza(float dt);
    void renderiza();
    void resetEstado();
    void acabaNivel(bool nvlAcabou);
};

}
