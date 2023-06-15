#pragma once

#include "stdafx.h"
#include "Estado.hpp"
#include <vector>
#include <map>

namespace GE {

class GerenciadorEstado {
protected:
    std::vector<Estado*> vectorDeEstados;
    GE::estadoID estadoAtualID;

public:
    GerenciadorEstado();
    virtual ~GerenciadorEstado();

    void mudarEstadoAtual(GE::estadoID id);
    void execEstadoAtual(float dt);
    estadoID getEstadoAtual() const;
};

}
