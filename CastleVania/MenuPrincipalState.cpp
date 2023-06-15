#include "MenuPrincipalState.hpp"
#include "Jogo.hpp"

using namespace GE;

MenuPrincipalState::MenuPrincipalState(GerenciadorInput* GI, Jogo* pJ) :
Menu(GI, BACKGROUND_MAIN_MENU),
Estado(static_cast<GerenciadorEstado*>(pJ)),
pJogo(pJ) {
    GerenciadorGrafico* GG = GerenciadorGrafico::getGerenciadorGrafico();
    Botao* bt = NULL;

    bt = new Botao(sf::Vector2f(GG->getWindowSize().x / 2.0f, GG->getWindowSize().y / 2));
    bt->setMensagem("NIVEL 1");
    bt->seleciona(true);
    vectorBotao.push_back(bt);

    bt = new Botao(sf::Vector2f(GG->getWindowSize().x / 2.0f, GG->getWindowSize().y / 2 + 80));
    bt->setMensagem("NIVEL 2");
    vectorBotao.push_back(bt);

    bt = new Botao(sf::Vector2f(GG->getWindowSize().x / 2.0f, GG->getWindowSize().y / 2 + 160));
    bt->setMensagem("CARREGAR");
    vectorBotao.push_back(bt);

    bt = new Botao(sf::Vector2f(GG->getWindowSize().x / 2.0f, GG->getWindowSize().y / 2 + 240));
    bt->setMensagem("PLACAR");
    vectorBotao.push_back(bt);

    bt = new Botao(sf::Vector2f(GG->getWindowSize().x / 2.0f, GG->getWindowSize().y / 2 + 320));
    bt->setMensagem("FECHAR");
    vectorBotao.push_back(bt);

    max = 4;
}

MenuPrincipalState::~MenuPrincipalState() {
}

void MenuPrincipalState::atualiza(float dt) {
    ativo = true;
}

/* Funcao para renderiza os objetos do menu. */
void MenuPrincipalState::renderiza() {
    atualizaView();
    back.renderiza();
    for (it = vectorBotao.begin(); it != vectorBotao.end(); ++it)
        (*it)->renderiza();
}

void MenuPrincipalState::exec() {
    if (ativo) {
        ativo = false;
        switch (selecionado) {
        case 0:
            pJogo->setNivelAtual(1);
            mudarEstado(estadoID::novoJogo);
            break;
        case 1:
            pJogo->setNivelAtual(2);
            mudarEstado(estadoID::novoJogo);
            break;
        case 2:
            mudarEstado(estadoID::carregarJogo);
            break;
        case 3:
            mudarEstado(estadoID::placar);
            break;
        case 4:
            pJogo->acabarJogo();
            break;
        default:
            break;
        }
    }
}

void MenuPrincipalState::resetEstado() {
    vectorBotao[selecionado]->seleciona(false);
    selecionado = 0;
    vectorBotao[selecionado]->seleciona(true);

    pJogo->deleteNivel();
    pJogo->resetJogadores();
    pJogo->setNivelAtual(1);
}
