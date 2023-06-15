#pragma once

#include "GerenciadorInput.hpp"
#include "stdafx.h"

class Observador {
private:
    GerenciadorInput* pGI;

public:
    Observador(GerenciadorInput* pGI);
    virtual ~Observador();
    virtual void notifica() = 0;
};
