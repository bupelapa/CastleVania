#include "GerenciadorEvento.hpp"

/* Padrao de projeto Singleton - Apenas uma instancia criada */
GerenciadorEvento* GerenciadorEvento::instancia = NULL;

GerenciadorEvento* GerenciadorEvento::getGerenciadorEvento() {
    if (instancia == NULL) {
        instancia = new GerenciadorEvento();
    }
    return instancia;
}

GerenciadorEvento::GerenciadorEvento() :
pGraphic(NULL),
pInput(NULL),
pWindow(NULL) {
    setGerenciadorGrafico();
}

/* ========================================= */

GerenciadorEvento::~GerenciadorEvento() {
    if (pInput)
        delete (pInput);
    pGraphic = NULL;
    pInput = NULL;
    pWindow = NULL;
}

void GerenciadorEvento::setGerenciadorGrafico() {
    pGraphic = GerenciadorGrafico::getGerenciadorGrafico();
    if (pGraphic != NULL)
        pWindow = pGraphic->getWindow();
}

void GerenciadorEvento::setGerenciadorInput(GerenciadorInput* pGI) {
    pInput = pGI;
}

void GerenciadorEvento::pollEventos() {
    sf::Event evento;

    while (pWindow->pollEvent(evento)) {
        if (evento.type == sf::Event::Closed)
            pGraphic->fecharJanela();
        if (evento.type == sf::Event::Resized)
            pGraphic->redefinirTamanhoJanela();
        if ((evento.type == sf::Event::KeyPressed || evento.type == sf::Event::KeyReleased) && pInput)
            pInput->teclaPressionada();
        if (evento.type == sf::Event::TextEntered)
            pInput->textoEscrito(evento);
    }
}

