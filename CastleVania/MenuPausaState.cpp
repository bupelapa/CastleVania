#include "MenuPausaState.hpp"
#include "Jogo.hpp"

using namespace GE;

MenuPausaState::MenuPausaState(GerenciadorInput* GI, Jogo* pJ) :
Menu(GI, BACKGROUND_PATH),
Estado(static_cast<GerenciadorEstado*>(pJ)),
pJogo(pJ) {
    GerenciadorGrafico* GG = GerenciadorGrafico::getGerenciadorGrafico();

    Botao* bt = NULL;

    bt = new Botao(sf::Vector2f(GG->getWindowSize().x / 2.0f, GG->getWindowSize().y / 2 - 80));
    bt->setMensagem("RESUME JOGO");
    bt->seleciona(true);
    vectorBotao.push_back(bt);

    bt = new Botao(sf::Vector2f(GG->getWindowSize().x / 2.0f, GG->getWindowSize().y / 2));
    bt->setMensagem("SALVAR");
    vectorBotao.push_back(bt);

    bt = new Botao(sf::Vector2f(GG->getWindowSize().x / 2.0f, GG->getWindowSize().y / 2 + 80));
    bt->setMensagem("MENU");
    vectorBotao.push_back(bt);

    selecionado = 0;
}

MenuPausaState::~MenuPausaState() { }

void MenuPausaState::atualiza(float dt) { }

/* Operacao do menu para renderiza objetos */
void MenuPausaState::renderiza() {
    atualizaView();
    back.renderiza();
    for (it = vectorBotao.begin(); it != vectorBotao.end(); ++it)
        (*it)->renderiza();
}

void MenuPausaState::exec() {
    if (ativo) {
        ativo = false;
        switch (selecionado) {
        case 0:
            mudarEstado(estadoID::jogando);
            break;
        case 1:
            pJogo->save();
            ativo = true;
            break;
        case 2:
            mudarEstado(estadoID::menuPrincipal);
            break;
        default:
            break;
        }
    }
    /* Trigger para abrir a pausa */
    else if (pJogo->getEstadoAtual() == estadoID::jogando) {
        mudarEstado(estadoID::menuPausa);
    }
}

void MenuPausaState::resetEstado() {
    vectorBotao[selecionado]->seleciona(false);
    selecionado = 0;
    vectorBotao[selecionado]->seleciona(true);
    ativo = true;
}
