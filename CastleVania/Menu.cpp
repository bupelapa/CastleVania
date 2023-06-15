#include "Menu.hpp"

#include "GerenciadorGrafico.hpp"

Menu::Menu(GerenciadorInput* GI, const char* planoPath) :
selecionado(0),
min(0),
max(2),
controle(GI, this),
back(sf::Vector2f(0, 0), planoPath),
ativo(false) {
    GerenciadorGrafico* GG = GerenciadorGrafico::getGerenciadorGrafico();
    back.mudarPos(sf::Vector2f(GG->getWindowSize().x / 2.0f, GG->getWindowSize().y / 2));
}

Menu::~Menu() {
    Botao* bt = NULL;
    while (vectorBotao.size() != 0) {
        bt = vectorBotao.back();
        delete (bt);
        vectorBotao.pop_back();
    }
    vectorBotao.clear();
}

/* Faz o selecionado do menu ir para cima */
void Menu::selecionaCima() {
    if (ativo) {
        vectorBotao[selecionado]->seleciona(false);
        selecionado++;
        if (selecionado > max)
            selecionado = max;
        vectorBotao[selecionado]->seleciona(true);
    }
}

/* Faz o selecionado do menu ir para baixo */
void Menu::selecionaBaixo() {
    if (ativo) {
        vectorBotao[selecionado]->seleciona(false);
        selecionado--;
        if (selecionado < min)
            selecionado = min;
        vectorBotao[selecionado]->seleciona(true);
    }
}

void Menu::atualizaView() {
    GerenciadorGrafico* GG = GerenciadorGrafico::getGerenciadorGrafico();
    GG->centerView(sf::Vector2f(640, 360));
}
