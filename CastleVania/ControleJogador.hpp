#pragma once

#include "stdafx.h"
#include "Observador.hpp"

class Jogador;
class GerenciadorInput;

class ControleJogador : public Observador {
private:
    Jogador* pJogador;
    sf::Keyboard::Key pula;
    sf::Keyboard::Key esquerda;
    sf::Keyboard::Key direita;
    sf::Keyboard::Key ataca;

public:
    ControleJogador(GerenciadorInput* pGI, Jogador* pJ = NULL);
    ~ControleJogador();

    void notifica();
    void addJogador(Jogador* p);
    /* Colocar no UML somente setKeys(jump: Key, left: Key...) */
    void setKeys(sf::Keyboard::Key pula, sf::Keyboard::Key esquerda, sf::Keyboard::Key direita, sf::Keyboard::Key ataca);
};
