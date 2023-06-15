#include "GerenciadorInput.hpp"

#include "Observador.hpp"

GerenciadorInput::GerenciadorInput() {
}

GerenciadorInput::~GerenciadorInput() {
    objObservado.clear();
}

/* Verifica tecla pressionada e notifica todos observadores */
void GerenciadorInput::teclaPressionada() {
    for (it = objObservado.begin(); it != objObservado.end(); ++it)
        (*it)->notifica();
}

/* Assina um observador para notificar caso algo aconteca */
void GerenciadorInput::Anexa(Observador* pObservar) {
    objObservado.push_back(pObservar);
}

void GerenciadorInput::Desanexa(Observador* pObservar) {
    objObservado.remove(pObservar);
}

void GerenciadorInput::textoEscrito(sf::Event eventCopy) {
    if (eventCopy.key.code == 8) {
        currentTextString = "";
    } else
        currentTextString += eventCopy.text.unicode;
}

sf::String GerenciadorInput::getString() {
    return currentTextString;
}

void GerenciadorInput::deleteString() {
    currentTextString.clear();
}

