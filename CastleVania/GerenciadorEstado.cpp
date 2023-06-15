#include "Estado.hpp"

#include "GerenciadorEstado.hpp"

using namespace GE;

GerenciadorEstado::GerenciadorEstado() {
}

GerenciadorEstado::~GerenciadorEstado() {
    Estado* st = NULL;
    while (vectorDeEstados.size() != 0) {
        st = vectorDeEstados.back();
        delete (st);
        vectorDeEstados.pop_back();
    }
    vectorDeEstados.clear();
}

void GerenciadorEstado::mudarEstadoAtual(GE::estadoID id) {
    estadoAtualID = id;
    vectorDeEstados[estadoAtualID]->resetEstado();
}

void GerenciadorEstado::execEstadoAtual(float dt) {

    vectorDeEstados[estadoAtualID]->atualiza(dt);
    vectorDeEstados[estadoAtualID]->renderiza();
}

estadoID GerenciadorEstado::getEstadoAtual() const {
    return estadoAtualID;
}
