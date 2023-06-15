#include "Jogo.hpp"


using namespace GE;

    Jogo::Jogo()

    {
        pEvento = GerenciadorEvento::getGerenciadorEvento();
        pGrafico = GerenciadorGrafico::getGerenciadorGrafico();

        pInput = new GerenciadorInput;
        pEvento->setGerenciadorInput(pInput);

        jogador1 = NULL;
        jogador2 = NULL;
        pNivel = NULL;
        nivelAcabou = false;

        iniciarEstados();
        Executar();
    }

    Jogo::~Jogo() {
    if (pNivel != NULL)
        delete (pNivel);
    if (jogador1)
        delete (jogador1);
    if (jogador2)
        delete (jogador2);
    }


void Jogo::iniciarEstados() {
    Estado* pNovoEstado = NULL;

    try {
        pNovoEstado = new MenuPrincipalState(pInput, this);
        if (pNovoEstado == NULL)
            throw 0;
        vectorDeEstados.push_back(pNovoEstado);

        pNovoEstado = new NovoJogoState(pInput, this);
        if (pNovoEstado == NULL)
            throw 0;
        vectorDeEstados.push_back(pNovoEstado);

        pNovoEstado = new JogandoJogoState(pInput, this);
        if (pNovoEstado == NULL)
            throw 0;
        vectorDeEstados.push_back(pNovoEstado);

        pNovoEstado = new MenuPausaState(pInput, this);
        if (pNovoEstado == NULL)
            throw 0;
        vectorDeEstados.push_back(pNovoEstado);

        pNovoEstado = new CarregaJogoState(pInput, this);
        if (pNovoEstado == NULL)
            throw 0;
        vectorDeEstados.push_back(pNovoEstado);

        pNovoEstado = new PontuacaoState(pInput, this);
        if (pNovoEstado == NULL)
            throw 0;
        vectorDeEstados.push_back(pNovoEstado);

        pNovoEstado = new AcabarJogoState(pInput, this);
        if (pNovoEstado == NULL)
            throw 0;
        vectorDeEstados.push_back(pNovoEstado);

    } catch (int err) {
        if (err == 0) {
            cout << "Erro alocando estados " << endl;
            exit(1);
        }
    }

    mudarEstadoAtual(estadoID::menuPrincipal);
}

    void Jogo::Executar() {
       float dt;
       time.restart();



        while (pGrafico->verificaJanelaAberta()) {
         /* Olha se algum evento aconteceu */
        pEvento->pollEventos();
         /* Tempo desde o ultimo loop */
         dt = time.getElapsedTime().asSeconds();
        time.restart();
        if (dt > 0.1)
            dt = 0.1;
        /* Limpa tela e desenha de novo */
        pGrafico->clear();
        /* Chama estado novo e renderiza */
         execEstadoAtual(dt);
        /* Mostra tudo desenhado */
        pGrafico->display();
    }
}

void Jogo::save() {
    if (pNivel != NULL)
        pNivel->saveNvl();
}

Nivel* Jogo::getpNivel() const {
    return pNivel;
}

void Jogo::setNivel(Nivel* pNivel) {
    this->pNivel = pNivel;
}

Jogador* Jogo::getJogador1() {
    if (jogador1 == NULL)
        jogador1 = new Jogador(true, pInput);
    return jogador1;
}

Jogador* Jogo::getJogador2() {
    if (jogador2 == NULL)
        jogador2 = new Jogador(false, pInput);
    return jogador2;
}

bool Jogo::doisJogadoresAtivos() const {
    return ((jogador1 != NULL) && (jogador2 != NULL));
}

int Jogo::getNivelAtual() const {
    return nivelAtual;
}

void Jogo::setNivelAtual(int num) {
    nivelAtual = num;
}

void Jogo::acabarJogo() {
    pGrafico->fecharJanela();
}

void Jogo::deleteNivel() {
    if (pNivel != NULL)
        delete (pNivel);
    pNivel = NULL;
}

void Jogo::resetJogadores() {
    if (jogador1 != NULL)
        delete jogador1;
    if (jogador2 != NULL)
        delete jogador2;
    jogador1 = NULL;
    jogador2 = NULL;
}

bool Jogo::taJogando() const {
    return nivelAcabou;
}

void Jogo::setNivelAcabou(bool x) {
    nivelAcabou = x;
}
