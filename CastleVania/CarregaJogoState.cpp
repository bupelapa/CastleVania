#include "CarregaJogoState.hpp"

#include "Jogo.hpp"
#include "Nivel.hpp"

using namespace GE;

CarregaJogoState::CarregaJogoState(GerenciadorInput* GI, Jogo* pJ) :
Estado(static_cast<GerenciadorEstado*>(pJ)),
pJogo(pJ) { }

CarregaJogoState::~CarregaJogoState() {
}

void CarregaJogoState::atualiza(float dt) {
    ConstrutorNivel* maker = new ConstrutorNivel();
    Nivel* nvl;

    ifstream Jogador2(("./Saves/Jogador2.txt"), ios::in);
    if (!Jogador2) {
        cout << "Erro ao carregar jogador em CarregarJogo" << endl;
        exit(100);
    }
    char info;

    if (Jogador2 >> info) {
        nvl = maker->carregarMapa(pJogo->getJogador1(), pJogo->getJogador2());
    } else
        nvl = maker->carregarMapa(pJogo->getJogador1(), NULL);
    Jogador2.close();

    if (!nvl) {
        cout << "ERRO CARREGANDO NIVEL" << endl;
        mudarEstado(estadoID::menuPrincipal);
    } else {
        pJogo->setNivel(nvl);
        mudarEstado(estadoID::jogando);
        pJogo->setNivelAtual(nvl->getNumNivel());
        pJogo->setNivelAcabou(false);
    }
    delete (maker);
}

void CarregaJogoState::renderiza() {
}

void CarregaJogoState::resetEstado() {
}
