#pragma once

#include "stdafx.h"
#include <list>

using namespace std;

class Observador;

class GerenciadorInput {
private:
    std::list<Observador*> objObservado;
    std::list<Observador*>::iterator it;
    sf::String currentTextString;

public:
    GerenciadorInput();
    ~GerenciadorInput();

    void Anexa(Observador* pObservador);
    void Desanexa(Observador* pObservador);
    void teclaPressionada();
    void textoEscrito(sf::Event eventCopy);
    sf::String getString();
    void deleteString();
};

