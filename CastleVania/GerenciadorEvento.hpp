#pragma once

#include "GerenciadorGrafico.hpp"
#include "GerenciadorInput.hpp"
#include "stdafx.h"

class GerenciadorEvento {
private:
    GerenciadorGrafico* pGraphic;
    GerenciadorInput* pInput;
    sf::RenderWindow* pWindow;

    /* Padrao de projeto Singleton */
    static GerenciadorEvento* instancia;
    GerenciadorEvento();

public:
    ~GerenciadorEvento();

    static GerenciadorEvento* getGerenciadorEvento();

    void setGerenciadorGrafico();
    void setGerenciadorInput(GerenciadorInput* pGI);

    void pollEventos();
};

