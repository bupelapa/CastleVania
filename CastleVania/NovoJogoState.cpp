#include "NovoJogoState.hpp"
#include "Jogo.hpp"

using namespace GE;

NovoJogoState::NovoJogoState(GerenciadorInput* GI, Jogo* pJ) :
Menu(GI, BACKGROUND_MAIN_MENU),
Estado(static_cast<GerenciadorEstado*>(pJ)),
pJogo(pJ) {
    GerenciadorGrafico* GG = GerenciadorGrafico::getGerenciadorGrafico();
    Botao* bt = NULL;

    bt = new Botao(sf::Vector2f(GG->getWindowSize().x / 2.0f, GG->getWindowSize().y / 2));
    bt->setMensagem("1-JOGADOR");
    bt->seleciona(true);
    vectorBotao.push_back(bt);

    bt = new Botao(sf::Vector2f(GG->getWindowSize().x / 2.0f, GG->getWindowSize().y / 2 + 80));
    bt->setMensagem("2-JOGADORES");
    vectorBotao.push_back(bt);

    bt = new Botao(sf::Vector2f(GG->getWindowSize().x / 2.0f, GG->getWindowSize().y / 2 + 160));
    bt->setMensagem("VOLTAR");
    vectorBotao.push_back(bt);

    selecionado = 0;

    max = 2;
}

NovoJogoState::~NovoJogoState() { }

void NovoJogoState::atualiza(float dt) {
    ativo = true;
}

/* Funcao para renderiza todos os objetos */
void NovoJogoState::renderiza() {
    atualizaView();
    back.renderiza();
    for (it = vectorBotao.begin(); it != vectorBotao.end(); ++it)
        (*it)->renderiza();
}

void NovoJogoState::exec() {
    if (ativo) {
        switch (selecionado) {
        case 0:
            comecaNovoNivel(true);
            break;
        case 1:
            comecaNovoNivel(false);
            break;
        case 2:
            mudarEstado(estadoID::menuPrincipal);
            break;
        default:
            break;
        }
    }
    ativo = false;
}

void NovoJogoState::comecaNovoNivel(bool eUmJogador) {
    Nivel* pNivel = NULL;
    int nivelAtual = pJogo->getNivelAtual();

    Jogador* jogador1 = pJogo->getJogador1();
    jogador1->reset();

    Jogador* jogador2 = NULL;

    if (!eUmJogador) {
        jogador2 = pJogo->getJogador2();
        jogador2->reset();
    }

    if (nivelAtual <= 1) {
        ConstrutorNivel* maker = new ConstrutorNivel();
        pNivel = maker->construirMapa(PATH_PLANODEFUNDO_PRIMEIRONIVEL, jogador1, jogador2, 1);
        delete (maker);
    } else if (nivelAtual == 2) {
        ConstrutorNivel* maker = new ConstrutorNivel();
        pNivel = maker->construirMapa(PATH_PLANODEFUNDO_SEGUNDONIVEL, jogador1, jogador2, 2);
        delete (maker);
    }

    else {
        cerr << "JOGO - Erro ao criar nivel - nao existe nivel" << endl;
        std::exit(35);
    }

    pJogo->setNivel(pNivel);
    pJogo->mudarEstadoAtual(estadoID::jogando);
}

void NovoJogoState::resetEstado() {
    if (!pJogo->taJogando()) {
        pJogo->deleteNivel();
        vectorBotao[selecionado]->seleciona(false);
        selecionado = 0;
        vectorBotao[selecionado]->seleciona(true);
    } else {
        pJogo->deleteNivel();
        comecaNovoNivel(!pJogo->doisJogadoresAtivos());
    }
}
