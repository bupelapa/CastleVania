#include "Nivel.hpp"

Nivel::Nivel(const char* path, Jogador* j1, Jogador* j2, sf::Vector2u nivelTamanho) :
Ggrafico(GerenciadorGrafico::getGerenciadorGrafico()),
_lista(new EntidadeLista()),
jogador1(j1),
jogador2(j2),
colis(_lista),
nivelMapaTamanho(nivelTamanho),
back(sf::Vector2f(float(Ggrafico->getWindowSize().x / 2), float(Ggrafico->getWindowSize().y / 2)), path),
chegouFinal(1000) {
    strcpy_s(this->path, path);
    pGerenEvento = GerenciadorEvento::getGerenciadorEvento();
    nivelRodando = 1;

    if (jogador1) {
        _lista->addEntidade(jogador1);
    }
    if (jogador2) {
        _lista->addEntidade(jogador2);
    }
}

Nivel::~Nivel() {
    if (jogador1) {
        _lista->removeEntidade(jogador1);
        jogador1 = NULL;
    }
    if (jogador2) {
        _lista->removeEntidade(jogador2);
        jogador2 = NULL;
    }
    delete (_lista);
}

void Nivel::exec(float dt) {
    if (jogador1->getAparece()) {
        if (jogador2 && !jogador2->getAparece())
            nivelRodando = 0;
        /* Atualiza todas as entidades */
        _lista->atualizaTudo(dt);
        /* Colide todas as entidades */
        colis.calculaColisao();
        //Condicao para acabar o nivel no final
        if (jogador1->getPosicao().x >= chegouFinal) {
            if (jogador2) {
                if (jogador2->getPosicao().x >= chegouFinal) {
                    nivelRodando = -1;
                } else
                    nivelRodando = 1;
            } else
                nivelRodando = -1;
        }
    } else
        nivelRodando = 0;
}

/* Roda todos eventos graficos */
void Nivel::renderizaTudo() {
    centerView();

    back.renderiza();

    for (int i = 0; i < _lista->getTamanho(); i++) {
        if ((*_lista)[i]->getAparece())
            (*_lista)[i]->renderiza();
    }
}

void Nivel::centerView() {
    sf::Vector2f verPosicao, verTamanho;

    if (jogador2 == NULL) {
        verPosicao = jogador1->getPosicao();
    } else {
        verPosicao = (jogador1->getPosicao() + jogador2->getPosicao()) / 2.0f;
    }

    Ggrafico->centerView(verPosicao);
    back.mudarPos(verPosicao);
}

void Nivel::saveNvl() {
    ofstream nivel;
    nivel.open("./Saves/Nivel.txt", ios::trunc);
    if (!nivel) {
        cout << "ERRO CARREGANDO NIVEL" << endl;
        abort();
    }
    nivel << path << ' ' << chegouFinal << endl;
    nivel.close();
    ofstream clean;
    clean.open("./assets/Saves/Jogador1.txt", ios::trunc);
    clean.close();
    clean.open("./assets/Saves/Mago.txt", ios::trunc);
    clean.close();
    clean.open("./assets/Saves/Ghoul.txt", ios::trunc);
    clean.close();
    clean.open("./assets/Saves/Parede.txt", ios::trunc);
    clean.close();
    clean.open("./assets/Saves/Jogador2.txt", ios::trunc);
    clean.close();
    clean.open("./assets/Saves/Plataforma.txt", ios::trunc);
    clean.close();
    clean.open("./assets/Saves/Espinho.txt", ios::trunc);
    clean.close();
    clean.open("./assets/Saves/Teia.txt", ios::trunc);
    clean.close();
    clean.open("./assets/Saves/Boss.txt", ios::trunc);
    clean.close();
    for (int i = 0; i < _lista->getTamanho(); i++) {
        (*_lista)[i]->save();
    }
}


int Nivel::getNumNivel() {
    if (!strcmp(path, PATH_PLANODEFUNDO_PRIMEIRONIVEL))
        return 1;
    else if (!strcmp(path, PATH_PLANODEFUNDO_SEGUNDONIVEL))
        return 2;
    return 0;
}
