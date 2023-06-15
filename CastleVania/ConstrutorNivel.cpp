#include "ConstrutorNivel.hpp"
ConstrutorNivel::ConstrutorNivel() {
    pJogador1 = NULL;
    pJogador2 = NULL;
}

ConstrutorNivel::~ConstrutorNivel() {
}

void ConstrutorNivel::construirPlataforma(sf::Vector2f pos, int tipo) {
    Plataforma* plat = new Plataforma(pos, tipo);
    nvl->addEntidade(plat);
}

void ConstrutorNivel::setJogador1(sf::Vector2f pos) {
    nvl->getJ1()->mudarPosicao(pos);
}
void ConstrutorNivel::setJogador1(sf::Vector2f pos, sf::Vector2f vel, int vida, int pontos, int olhandoEsquerda) {
    nvl->getJ1()->mudarPosicao(pos);
    nvl->getJ1()->setVelocidade(vel);
    nvl->getJ1()->setVida(vida);
    nvl->getJ1()->setPontos(pontos);
    nvl->getJ1()->setOlhandoEsquerda(olhandoEsquerda);
}

void ConstrutorNivel::setJogador2(sf::Vector2f pos) {
    if (nvl->getJ2())
        nvl->getJ2()->mudarPosicao(pos);
}
void ConstrutorNivel::setJogador2(sf::Vector2f pos, sf::Vector2f vel, int vida, int pontos, int olhandoEsquerda) {
    if (nvl->getJ2()) {
        nvl->getJ2()->mudarPosicao(pos);
        nvl->getJ2()->setVelocidade(vel);
        nvl->getJ2()->setVida(vida);
        nvl->getJ2()->setPontos(pontos);
        nvl->getJ2()->setOlhandoEsquerda(olhandoEsquerda);
    }
}

void ConstrutorNivel::construirMago(sf::Vector2f pos) {
    BolaDeFogo* bf = new BolaDeFogo(pos);
    Mago* mg = new Mago(pos, bf, pJogador1, pJogador2);
    nvl->addEntidade(bf);
    nvl->addEntidade(mg);
}

void ConstrutorNivel::construirMago(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f posProj, sf::Vector2f velProj, int aparece, int vida, int olhandoEsquerda, int minH, int maxH) {
    BolaDeFogo* bf = new BolaDeFogo(posProj);
    Mago* mg = new Mago(pos, bf, pJogador1, pJogador2, minH, maxH);
    nvl->addEntidade(bf);
    nvl->addEntidade(mg);
    bf->setAparece(aparece);
    bf->setVelocidade(velProj);
    bf->mudarPosicao(posProj);
    mg->setVelocidade(vel);
    mg->setVida(vida);
    mg->setOlhandoEsquerda(olhandoEsquerda);
}

void ConstrutorNivel::construirGhoul(sf::Vector2f pos) {
    Ghoul* ghoul = new Ghoul(pos, pJogador1, pJogador2);
    nvl->addEntidade(ghoul);
}

void ConstrutorNivel::construirGhoul(sf::Vector2f pos, int vida, int olhandoEsquerda) {
    Ghoul* ghoul = new Ghoul(pos, pJogador1, pJogador2);
    nvl->addEntidade(ghoul);
    ghoul->setVida(vida);
    ghoul->setOlhandoEsquerda(olhandoEsquerda);
}

void ConstrutorNivel::construirBoss(sf::Vector2f pos) {
    Raio* raio = new Raio(pos);
    Boss* boss = new Boss(pos, raio, pJogador1, pJogador2);
    nvl->addEntidade(raio);
    nvl->addEntidade(boss);
}
void ConstrutorNivel::construirBoss(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f posProj, sf::Vector2f velProj, int aparece, int vida, int olhandoEsquerda, int minH, int maxH, int minD, int maxD) {
    Raio* raio = new Raio(posProj);
    Boss* boss = new Boss(pos, raio, pJogador1, pJogador2, minH, maxH, minD, maxD);
    nvl->addEntidade(raio);
    raio->setAparece(aparece);
    raio->setVelocidade(velProj);
    raio->mudarPosicao(posProj);
    nvl->addEntidade(boss);
    boss->setVelocidade(vel);
    boss->setVida(vida);
    boss->setOlhandoEsquerda(olhandoEsquerda);
}

void ConstrutorNivel::construirParede(sf::Vector2f pos, int tipo, bool olhaEsquerda) {
    Parede* parede = new Parede(pos, tipo, olhaEsquerda);
    nvl->addEntidade(parede);
}

void ConstrutorNivel::construirTeia(sf::Vector2f pos) {
    Teia* teia = new Teia(pos);
    nvl->addEntidade(teia);
}

void ConstrutorNivel::construirEspinho(sf::Vector2f pos) {
    Espinho* espinho = new Espinho(pos);
    nvl->addEntidade(espinho);
}

#define PATH_PLANODEFUNDO_PRIMEIRONIVEL "./imagens/FundoNivelUm.png"
#define PATH_PLANODEFUNDO_SEGUNDONIVEL "./imagens/FundoNivelDois.png"

Nivel* ConstrutorNivel::construirMapa(const char* path, Jogador* j1, Jogador* j2, int numnvl) {
    pJogador1 = j1;
    pJogador2 = j2;

    int y = 30, x = 80;
    char nivel[30][80];
    srand(time(NULL));
    ifstream file;
    if (numnvl <= 1) {
        file.open("./mapa/PrimeiroNivel.txt");
        nvl = new Nivel(PATH_PLANODEFUNDO_PRIMEIRONIVEL, j1, j2, sf::Vector2u(80 * PLATAFORMA_LARGURA, 40 * PLATAFORMA_ALTURA));
    } else if (numnvl == 2) {
        file.open("./mapa/SegundoNivel.txt");
        nvl = new Nivel(PATH_PLANODEFUNDO_SEGUNDONIVEL, j1, j2, sf::Vector2u(80 * PLATAFORMA_LARGURA, 40 * PLATAFORMA_ALTURA));
    }
    if (!file) {
        cout << "Erro abrindo mapa no ConstrutorNivel" << endl;
        std::exit(54);
    }

    file >> nivel[0][0];
    while (!file.eof()) {
        file.ignore();
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                if (i || j)
                    file >> nivel[i][j];
                if (nivel[i][j] == txt::plataforma) {
                    construirPlataforma(sf::Vector2f(j * PLATAFORMA_LARGURA, i * PAREDE_ALTURA), numnvl);
                } else if (nivel[i][j] == txt::jogador1) {
                    setJogador1(sf::Vector2f(j * PLATAFORMA_LARGURA, i * PAREDE_ALTURA));
                } else if (nivel[i][j] == txt::mago) {
                    construirMago(sf::Vector2f(j * PLATAFORMA_LARGURA, i * PAREDE_ALTURA));
                } else if (nivel[i][j] == txt::jogador2) {
                    setJogador2(sf::Vector2f(j * PLATAFORMA_LARGURA, i * PAREDE_ALTURA));
                } else if (nivel[i][j] == txt::ghoul) {
                    construirGhoul(sf::Vector2f(j * PLATAFORMA_LARGURA, i * PAREDE_ALTURA));
                } else if (nivel[i][j] == txt::paredeEsquerda) {
                    construirParede(sf::Vector2f(j * PLATAFORMA_LARGURA + (PLATAFORMA_LARGURA - PAREDE_LARGURA) / 2, i * PAREDE_ALTURA), numnvl, true);
                } else if (nivel[i][j] == txt::paredeDireita) {
                    construirParede(sf::Vector2f(j * PLATAFORMA_LARGURA - (PLATAFORMA_LARGURA - PAREDE_LARGURA) / 2, i * PAREDE_ALTURA), numnvl, false);
                } else if (nivel[i][j] == txt::teia) {
                    construirTeia(sf::Vector2f(j * PLATAFORMA_LARGURA, i * PAREDE_ALTURA));
                } else if (nivel[i][j] == txt::espinho) {
                    construirEspinho(sf::Vector2f(j * PLATAFORMA_LARGURA, i * PAREDE_ALTURA));
                } else if (nivel[i][j] == txt::ghoulRand) {
                    int random = rand() % 10;
                    if (random >= 5)
                        construirGhoul(sf::Vector2f(j * PLATAFORMA_LARGURA, i * PAREDE_ALTURA));
                } else if (nivel[i][j] == txt::magoRand) {
                    int random = rand() % 10;
                    if (random >= 5)
                        construirMago(sf::Vector2f(j * PLATAFORMA_LARGURA, i * PAREDE_ALTURA));
                } else if (nivel[i][j] == txt::espinhoRand) {
                    int random = rand() % 10;
                    if (random >= 5)
                        construirEspinho(sf::Vector2f(j * PLATAFORMA_LARGURA, i * PAREDE_ALTURA));
                } else if (nivel[i][j] == txt::teiaRand) {
                    int random = rand() % 10;
                    if (random >= 5)
                        construirTeia(sf::Vector2f(j * PLATAFORMA_LARGURA, i * PAREDE_ALTURA));
                } else if (nivel[i][j] == txt::boss) {
                    construirBoss(sf::Vector2f(j * PLATAFORMA_LARGURA, i * PAREDE_ALTURA));
                } else if (nivel[i][j] == txt::end) {
                    nvl->setFim(j * PLATAFORMA_LARGURA);
                }
            }
        }
    }
    file.close();
    return nvl;
}

Nivel* ConstrutorNivel::carregarMapa(Jogador* j1, Jogador* j2) {
    pJogador1 = j1;
    pJogador2 = j2;

    char path[100];
    int end;
    ifstream Niveltxt("./Saves/Nivel.txt", ios::in);
    if (!Niveltxt) {
        cout << "Erro ao abrir texto em CarregarMapa" << endl;
        exit(100);
    }

    Niveltxt >> path >> end;
    Niveltxt.close();

    nvl = new Nivel(path, j1, j2, sf::Vector2u(80 * PLATAFORMA_LARGURA, 26 * PLATAFORMA_ALTURA));

    nvl->setFim(end);
    if (!path) {
        cout << "Nenhum nivel salvo" << endl;
        exit(99);
    }

    sf::Vector2f pos;
    bool olhandoEsquerda;
    bool aparece;
    sf::Vector2f posProj;
    sf::Vector2f velProj;
    sf::Vector2f vel;
    int vida, pontos;

/* ************************************************************************* */
    ifstream Jogador1(("./Saves/Jogador1.txt"), ios::in);
    if (!Jogador1) {
        cout << "Erro ao abrir Jogador1 em CarregarMapa" << endl;
        exit(100);
    }
    Jogador1 >> pos.x >> pos.y >> vel.x >> vel.y >> vida >> pontos >> olhandoEsquerda;
    setJogador1(sf::Vector2f(pos), sf::Vector2f(vel), vida, pontos, olhandoEsquerda);
    Jogador1.close();

/* ************************************************************************* */

    if (j2 != NULL) {
        ifstream Jogador2(("./Saves/Jogador2.txt"), ios::in);
        if (!Jogador2) {
            cout << "Erro ao abrir Jogador2 em CarregarMapa" << endl;
            exit(100);
        }

        Jogador2 >> pos.x >> pos.y >> vel.x >> vel.y >> vida >> pontos >> olhandoEsquerda;
        setJogador2(sf::Vector2f(pos), sf::Vector2f(vel), vida, pontos, olhandoEsquerda);
        Jogador2.close();
    }
/* ************************************************************************* */

    int tipo;
    ifstream Plataforma(("./Saves/Plataforma.txt"), ios::in);
    if (!Plataforma) {
        cout << "Erro ao abrir Plataforma em CarregarMapa" << endl;
        exit(100);
    }
    while (Plataforma >> pos.x >> pos.y >> tipo)
        construirPlataforma(sf::Vector2f(pos.x, pos.y), tipo);
    Plataforma.close();
/* ************************************************************************* */

    ifstream Parede(("./Saves/Parede.txt"), ios::in);
    if (!Parede) {
        cout << "Erro ao abrir parede em CarregarMapa" << endl;
        exit(100);
    }

    while (Parede >> pos.x >> pos.y >> olhandoEsquerda >> tipo) {
        construirParede(sf::Vector2f(pos.x, pos.y), tipo, olhandoEsquerda);
    }
    Parede.close();
/* ************************************************************************* */

    ifstream Teia(("./Saves/Teia.txt"), ios::in);
    if (!Teia) {
        cout << "Erro ao abrir Teia em CarregarMapa" << endl;
        exit(100);
    }
    while (Teia >> pos.x >> pos.y)
        construirTeia(sf::Vector2f(pos.x, pos.y));
    Teia.close();
/* ************************************************************************* */

    ifstream Espinho(("./Saves/Espinho.txt"), ios::in);
    if (!Espinho) {
        cout << "Erro ao abrir espinho em CarregarMapa" << endl;
        exit(100);
    }
    while (Espinho >> pos.x >> pos.y)
        construirEspinho(sf::Vector2f(pos.x, pos.y));
    Espinho.close();
/* ************************************************************************* */

    ifstream Ghoul("./Saves/Ghoul.txt");
    if (!Ghoul) {
        cout << "Erro ao abrir Ghoul em CarregarMapa" << endl;
        exit(100);
    }
    while (Ghoul >> pos.x >> pos.y >> vel.x >> vel.y >> vida >> olhandoEsquerda)
        construirGhoul(pos, vida, olhandoEsquerda);
    Ghoul.close();
/* ************************************************************************* */

    ifstream Mago("./Saves/Mago.txt");
    if (!Mago) {
        cout << "Erro ao abrir Mago em CarregarMapa" << endl;
        exit(100);
    }
    int minH, maxH;
    while (Mago >> pos.x >> pos.y >> vel.x >> vel.y >> posProj.x >> posProj.y >> velProj.x >> velProj.y >> aparece >> vida >> olhandoEsquerda >> minH >> maxH)
        construirMago(pos, vel, posProj, velProj, aparece, vida, olhandoEsquerda, minH, maxH);
    Mago.close();
/* ************************************************************************* */

    ifstream Boss("./Saves/Boss.txt");
    if (!Boss) {
        cout << "Erro ao abrir Boss em CarregarMapa" << endl;
        exit(100);
    }
    int minD, maxD;
    if (Boss >> pos.x >> pos.y >> vel.x >> vel.y >> posProj.x >> posProj.y >> velProj.x >> velProj.y >> aparece >> vida >> olhandoEsquerda >> minH >> maxH >> minD >> maxD)
        construirBoss(pos, vel, posProj, velProj, aparece, vida, olhandoEsquerda, minH, maxH, minD, maxD);
    Boss.close();
/* ************************************************************************* */

    return nvl;
}
