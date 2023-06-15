#include "Observador.hpp"

Observador::Observador(GerenciadorInput* pGI) {
    this->pGI = pGI;
    pGI->Anexa(this);
}

Observador::~Observador(){
    pGI->Desanexa(this);
    pGI = NULL;
}
