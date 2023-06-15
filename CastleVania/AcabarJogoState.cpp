#include "AcabarJogoState.hpp"
#include "Jogo.hpp"
#include "GerenciadorGrafico.hpp"
#include "Nivel.hpp"

using namespace GE;

AcabarJogoState::AcabarJogoState(GerenciadorInput* GI, Jogo* pJ) :
Menu(GI, PLANODEFUNDO_PRINCIPAL),
Estado(static_cast<GerenciadorEstado*>(pJ)),
pJogo(pJ),
pGI(GI),
nomeJ("") {
    GG = GerenciadorGrafico::getGerenciadorGrafico();

    Botao* bt;
    bt = new Botao(sf::Vector2f(GG->getWindowSize().x / 2.0f, GG->getWindowSize().y / 2 + 150));
    bt->setMensagem("confirmar");
    bt->seleciona(true);
    vectorBotao.push_back(bt);

    textoFimDeJogo.setFont(*(GG->getFont()));
    textoFimDeJogo.setCharacterSize(TEXT_SIZE * 4);
    textoFimDeJogo.setFillColor(sf::Color::Black);

    textoFimDeJogo.setString("FIM DE JOGO");
    sf::FloatRect textoRect = textoFimDeJogo.getLocalBounds();
    textoFimDeJogo.setOrigin(textoRect.left + textoRect.width / 2.0f, textoRect.top + textoRect.height / 2.0f);
    textoFimDeJogo.setPosition(sf::Vector2f(GG->getWindowSize().x / 2, (GG->getWindowSize().y / 2) - 80));

    texto.setFont(*(GG->getFont()));
    texto.setCharacterSize(TEXT_SIZE);
    texto.setFillColor(sf::Color::White);
}

AcabarJogoState::~AcabarJogoState() {
}

void AcabarJogoState::atualiza(float dt) {
    ativo = true;
    atualizaNome();
}

void AcabarJogoState::renderiza() {
    atualizaView();
    back.renderiza();
    for (it = vectorBotao.begin(); it != vectorBotao.end(); ++it)
        (*it)->renderiza();
    GG->desenhaElemento(&textoFimDeJogo);
    GG->desenhaElemento(&texto);
}

void AcabarJogoState::resetEstado() {
    pGI->deleteString();
    apelido.clear();
    strcpy_s(nomeJ, "");
}

void AcabarJogoState::exec() {
    if (ativo) {
        if (apelido.getSize() > 0) {
            salvaPontos();
            mudarEstado(estadoID::menuPrincipal);
        }
        ativo = false;
    }
}

void AcabarJogoState::atualizaNome() {
    sf::String string;
    apelido = pGI->getString();
    string = "Primeiro Nome: " + apelido;
    texto.setString(string);
    sf::FloatRect textoRect = texto.getLocalBounds();
    texto.setOrigin(textoRect.left + textoRect.width / 2.0f, textoRect.top + textoRect.height / 2.0f);
    texto.setPosition(sf::Vector2f(640, 360));
}

void AcabarJogoState::salvaPontos() {
    int pontosP = getPontos();
    if (pontosP <= 0)
        return;

    std::string s1 = apelido;
    strcpy_s(nomeJ, "-");
    for (int i = 0; s1[i] != 32 && s1[i] != 0 && s1[i] != 13; i++)
        nomeJ[i + 1] = s1[i];

    ifstream getFile(("./Saves/Placar.txt"), ios::in);

    if (!getFile) {
        cout << "ERRO AO ABRIR PLACAR" << endl;
        abort();
    }
    char names[10][30];
    int pontos[10];
    int i;
    for (i = 0; i < 10; i++) {
        getFile >> names[i] >> pontos[i];
    }
    getFile.close();

    int min = 0, pos = 0;

    for (i = 0; i < 10; i++) {
        if (min >= pontos[i]) {
            min = pontos[i];
            pos = i;
        }
    }
    if (pontos[pos] <= pontosP) {
        pontos[pos] = pontosP;
        strcpy_s(names[pos], nomeJ);
    }
    char aux[30];
    for (i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (pontos[j] > pontos[i]) {
                strcpy_s(aux, names[j]);
                int ptaux = pontos[j];
                strcpy_s(names[j], names[i]);
                pontos[j] = pontos[i];
                strcpy_s(names[i], aux);
                pontos[i] = ptaux;
            }
        }
    }
    ofstream setFile;
    setFile.open("./Saves/Placar.txt", ios::trunc);
    if (!setFile) {
        cout << "ERRO AO ABRIR PLACAR" << endl;
        abort();
    }
    for (i = 0; i < 10; i++)
        setFile << names[i] << ' ' << pontos[i] << endl;

    setFile.close();
}

int AcabarJogoState::getPontos() {
    return pJogo->getJogador1()->getPontos() + pJogo->getJogador2()->getPontos();
}
