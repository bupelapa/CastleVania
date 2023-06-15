#pragma once

#include "stdafx.h"

namespace GE {

class GerenciadorEstado;

enum estadoID {
    menuPrincipal = 0,
    novoJogo,
    jogando,
    menuPausa,
    carregarJogo,
    placar,
    acabarJogo
};

class Estado {

private:
    GerenciadorEstado* pGE;

public:
    Estado(GerenciadorEstado* pGE = NULL);
    virtual ~Estado();

    void setGerenciadorEstado(GerenciadorEstado* pGE);
    void mudarEstado(GE::estadoID id);
    virtual void atualiza(float dt) = 0;
    virtual void renderiza() = 0;
    virtual void resetEstado() = 0;
};

}
