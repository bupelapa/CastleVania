#include "ControleMenu.hpp"

#include "GerenciadorInput.hpp"
#include "Menu.hpp"

ControleMenu::ControleMenu(GerenciadorInput* pGI, Menu* pM) :
Observador(pGI),
pMenu(pM) { }

ControleMenu::~ControleMenu() {
    pMenu = NULL;
}

void ControleMenu::notifica() {

    if (pMenu == NULL) {
        cout << "ERROR pointer apontado para Menu NULL em ControleMenu::notifica()." << endl;
        exit(7);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        pMenu->selecionaCima();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        pMenu->selecionaBaixo();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        pMenu->exec();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        pMenu->exec();
}

void ControleMenu::addMenu(Menu* p) {
    pMenu = p;
}

