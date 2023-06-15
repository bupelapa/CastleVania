#include "JogandoJogoState.hpp"
#include "Jogo.hpp"
#include "Nivel.hpp"

using namespace GE;

JogandoJogoState::JogandoJogoState(GerenciadorInput* GI, Jogo* pJ) :
Estado(static_cast<GerenciadorEstado*>(pJ)),
pJogo(pJ) {
    pNivel = NULL;
}

JogandoJogoState::~JogandoJogoState() {
}

void JogandoJogoState::atualiza(float dt) {
    pNivel->exec(dt);

    if (pNivel->nivelTaRodando() == 0)
        acabaNivel(false);
    else if (pNivel->nivelTaRodando() == -1)
        acabaNivel(true);
}

void JogandoJogoState::renderiza() {
    pNivel->renderizaTudo();
}

void JogandoJogoState::acabaNivel(bool nvlAcabou) {
    pNivel = NULL;
    if (nvlAcabou) {
        if (pJogo->getNivelAtual() == 2) {
            pJogo->setNivelAcabou(false);
            mudarEstado(estadoID::acabarJogo);
        } else {
            pJogo->setNivelAcabou(true);
            pJogo->setNivelAtual(2);
            mudarEstado(estadoID::novoJogo);
        }
    } else {
        pJogo->setNivelAcabou(false);
        mudarEstado(estadoID::acabarJogo);
    }
}

void JogandoJogoState::resetEstado() {
    pNivel = pJogo->getpNivel();
}
