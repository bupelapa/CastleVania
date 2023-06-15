#include "PontuacaoState.hpp"
#include "Jogo.hpp"

using namespace GE;

PontuacaoState::PontuacaoState(GerenciadorInput* GI, Jogo* pJ) :
Menu(GI, PLANODEFUNDO_PRINCIPAL),
Estado(static_cast<GerenciadorEstado*>(pJ)),
pJogo(pJ) {
    GG = GerenciadorGrafico::getGerenciadorGrafico();
    Botao* bt = NULL;

    bt = new Botao(sf::Vector2f(GG->getWindowSize().x / 2.0f, 13 * 48));
    bt->setMensagem("Voltar para o menu");
    bt->seleciona(true);
    vectorBotao.push_back(bt);

    sf::Text* texto;
    for (int i = 0; i < 10; i++) {
        texto = new Text();

        texto->setFont(*(GG->getFont()));
        texto->setCharacterSize(TEXT_SIZE);
        texto->setFillColor(sf::Color::White);

        vectorOfTexts.push_back(texto);
    }

    max = 0;
}

PontuacaoState::~PontuacaoState() {
    sf::Text* texto = NULL;
    while (vectorOfTexts.size() != 0) {
        texto = vectorOfTexts.back();
        delete (texto);
        vectorOfTexts.pop_back();
    }
    vectorOfTexts.clear();
}

void PontuacaoState::atualiza(float dt) {
    ativo = true;
}

/* Funcao do menu de renderizar todos os elementos */
void PontuacaoState::renderiza() {
    atualizaView();
    back.renderiza();
    for (it = vectorBotao.begin(); it != vectorBotao.end(); ++it)
        (*it)->renderiza();
    for (itr = vectorOfTexts.begin(); itr != vectorOfTexts.end(); ++itr)
        GG->desenhaElemento(*(itr));
}

void PontuacaoState::exec() {
    if (ativo) {
        switch (selecionado) {
        case 0:
            mudarEstado(estadoID::menuPrincipal);
            break;
        default:
            break;
        }
    }
    ativo = false;
}

void PontuacaoState::resetEstado() {
    ifstream textFile(LEADERBOARD_TXT_PATH, ios::in);
    if (!textFile) {
        cout << "ERRO ABRINDO TEXTO DO MAPA" << endl;
        exit(100);
    }

    sf::String string;
    char nome[100];
    sf::Text* texto;

    int ponto, j, count;
    for (int i = 1; i < 11; i++) {
        texto = vectorOfTexts[i - 1];
        textFile >> nome >> ponto;

        string = to_string(i);
        string += "  ";
        string += nome;

        count = 0;
        for (j = 0; nome[j] != '\0'; j++) {
            count++;
        }

        for (j = 0; j < 30 - count; j++) {
            string += '_';
        }

        string += to_string(ponto);

        texto->setString(string);
        sf::FloatRect textRect = texto->getLocalBounds();
        texto->setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        texto->setPosition(sf::Vector2f(640, 48 + (i)*48));
    }

    textFile.close();
}

