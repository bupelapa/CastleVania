#include "GerenciadorColisao.hpp"
#include "Jogador.hpp"

GerenciadorColisao::GerenciadorColisao(EntidadeLista* pLista):
list(pLista) {
}

GerenciadorColisao::~GerenciadorColisao()
{
    list = NULL;
}

//Intera toda a lista de entidades e calcula colisao entre elas, seja inimigo, jogador, projetil ou obstaculo.
void GerenciadorColisao::calculaColisao()
{
    Entidade *ent1, *ent2;
    // @ Alternativa de função de colisão, talvez seja mais eficiente
    for (int i = 0; i < list->getTamanho(); i++) {
        for (int j = i + 1; j < list->getTamanho(); j++) {
            ent1 = (*list)[i];
            ent2 = (*list)[j];
            if (ent1->getAparece() && ent2->getAparece()) {
                bool ataqueP = ((ent1->getId() == ID::jogador && (ent2->getId() == ID::mago || ent2->getId() == ID::ghoul || ent2->getId() == ID::boss)) || (ent2->getId() == ID::jogador && (ent1->getId() == ID::mago || ent1->getId() == ID::ghoul || ent1->getId() == ID::boss)));

                float dy, dx, intersectaX, intersectaY;
                dx = ent2->getPosicao().x - ent1->getPosicao().x;
                dy = ent2->getPosicao().y - ent1->getPosicao().y;

                intersectaX = abs(dx) - (ent1->getHitbox().x / 2 + ent2->getHitbox().x / 2);
                intersectaY = abs(dy) - (ent1->getHitbox().y / 2 + ent2->getHitbox().y / 2);

                if (ataqueP) {
                    ataqueJogador(ent1, ent2, dx, dy);
                }
                if (intersectaX < 0.0f && intersectaY < 0.0f) { //Condicao para colidir
                    if (ent1->getId() == ID::jogador || ent1->getId() == ID::jogador2) {
                        colidirJogador(ent1, ent2, dx, dy, intersectaX, intersectaY);
                    } else if (ent1->getId() == ID::mago || ent1->getId() == ID::ghoul || ent1->getId() == ID::boss) {
                        colidirInimigo(ent1, ent2, dx, dy, intersectaX, intersectaY);
                    } else if (ent1->getId() == ID::boladefogo || ent1->getId() == ID::raio) {
                        colidirProjetil(ent1, ent2, dx, dy, intersectaX, intersectaY);
                    } else if (ent1->getId() == ID::plataforma || ent1->getId() == ID::parede) {
                        colidirPlataforma(ent1, ent2, dx, dy, intersectaX, intersectaY);
                    }
                }
            }
        }
    }

}

//funcao para entidades andarem usando a velocidade de referencia delas (eixo X)
void GerenciadorColisao::andaX(Entidade* ent1, Entidade* ent2, float intersectaX) {
    ent1->Mover(sf::Vector2f(intersectaX * ent1->getVelocidade().x / ((abs(ent1->getVelocidade().x) + abs(ent2->getVelocidade().x) + DIV0)), 0.0f));
    ent2->Mover(sf::Vector2f(intersectaX * ent2->getVelocidade().x / ((abs(ent1->getVelocidade().x) + abs(ent2->getVelocidade().x) + DIV0)), 0.0f));
    ent1->setVelocidade(sf::Vector2f(0.0f, ent1->getVelocidade().y));
    ent2->setVelocidade(sf::Vector2f(0.0f, ent2->getVelocidade().y));
}

//funcao para entidades andarem usando a velocidade de referencia delas (eixo Y)
void GerenciadorColisao::andaY(Entidade* ent1, Entidade* ent2, float intersectaY) {

    ent1->Mover(sf::Vector2f(0.0f, intersectaY * ent1->getVelocidade().y / ((abs(ent1->getVelocidade().y) + abs(ent2->getVelocidade().y) + DIV0))));
    ent2->Mover(sf::Vector2f(0.0f, intersectaY * ent2->getVelocidade().y / ((abs(ent1->getVelocidade().y) + abs(ent2->getVelocidade().y) + DIV0))));

    ent1->setVelocidade(sf::Vector2f(ent1->getVelocidade().x, 0.0f));
    ent2->setVelocidade(sf::Vector2f(ent2->getVelocidade().x, 0.0f));
}

//jogador não pode ficar em cima de inimigo e vice versa
void GerenciadorColisao::emCima(Entidade* ent1, Entidade* ent2, float intersectaX, float dx) {
    if (ent1->getPosicao().y > ent2->getPosicao().y){
        if (dx > 0)
            ent2->Mover(sf::Vector2f(-intersectaX, 0.0f));
        else
            ent2->Mover(sf::Vector2f(intersectaX, 0.0f));
    }
    else if (dx > 0)
        ent1->Mover(sf::Vector2f(-intersectaX, 0.0f));
    else
        ent1->Mover(sf::Vector2f(intersectaX, 0.0f));
}

//funcao para colidir jogador com outras entidades
void GerenciadorColisao::colidirJogador(Entidade* ent1, Entidade* ent2, float dx, float dy, float intersectaX, float intersectaY) {
    switch (ent2->getId()) {

    case ID::plataforma:
        if (intersectaX > intersectaY) {
            andaX(ent1, ent2, intersectaX);
            ent1->setVelocidade(sf::Vector2f(0, ent1->getVelocidade().y));
        } else {
            if (dy > 0.0f) {
                andaY(ent1, ent2, intersectaY);
                (static_cast<Jogador*>(ent1))->setPulo(true);
            } else {
                andaY(ent1, ent2, intersectaY);
            }
        }
        break;
    case ID::parede:
        if (intersectaX > intersectaY) {
            andaX(ent1, ent2, intersectaX);
            ent1->setVelocidade(sf::Vector2f(0, ent1->getVelocidade().y));
        }

        break;

    case ID::mago:
        if (intersectaX > intersectaY) {
            andaX(ent1, ent2, intersectaX);

        } else {
            emCima(ent1, ent2, intersectaX, dx);
        }
        break;
    case ID::ghoul:
        if (intersectaX > intersectaY) {
            andaX(ent1, ent2, intersectaX);

        } else {
            emCima(ent1, ent2, intersectaX, dx);
        }
        break;
    case ID::boss:
        if (intersectaX > intersectaY) {
            andaX(ent1, ent2, intersectaX);

        } else {
            emCima(ent1, ent2, intersectaX, dx);
        }
        break;
    case ID::boladefogo:
        ataqueInimigo(ent2, ent1);
        break;
    case ID::raio:
        ataqueInimigo(ent2, ent1);
        break;
    case ID::espinho:
        (static_cast<Personagem*>(ent1))->tomaDano(static_cast<Obstaculo*>(ent2)->getEfeito());
        break;
    case ID::teia:
        ent1->setVelocidade(ent1->getVelocidade() / (static_cast<Obstaculo*>(ent2)->getEfeito()));
        break;
    default:
        break;
    }
}

//funcao para colidir inimigos com outras entidades
void GerenciadorColisao::colidirInimigo(Entidade* ent1, Entidade* ent2, float dx, float dy, float intersectaX, float intersectaY) {
    switch (ent2->getId()) {

    case ID::empty:
        break;

    case ID::jogador:
        if (intersectaX > intersectaY) {
            andaX(ent1, ent2, intersectaX);
        } else {
            emCima(ent1, ent2, intersectaX, dx);
        }
        break;

    case ID::jogador2:
        if (intersectaX > intersectaY) {
            andaX(ent1, ent2, intersectaX);
        } else {
            emCima(ent1, ent2, intersectaX, dx);
        }
        break;

    case ID::plataforma:
        if (intersectaX > intersectaY) {
            andaX(ent1, ent2, intersectaX);
        } else {
            andaY(ent1, ent2, intersectaY);
        }
        break;
    case ID::parede:
        if (intersectaX > intersectaY) {
            andaX(ent1, ent2, intersectaX);
        }
        break;
    default:
        break;
    }
}

//funcao para colidir projeteis com outras entidades
void GerenciadorColisao::colidirProjetil(Entidade* ent1, Entidade* ent2, float dx, float dy, float intersectaX, float intersectaY) {
    switch (ent2->getId()) {

    case ID::empty:
        break;

    case ID::jogador:
        ataqueInimigo(ent1, ent2);
        break;

    case ID::jogador2:
        ataqueInimigo(ent1, ent2);
        break;

    case ID::plataforma:
        ent1->setAparece(false);
        break;
    case ID::parede:
        ent1->setAparece(false);

    default:
        break;
    }
}
//funcao para colidir projetil com jogador
void GerenciadorColisao::ataqueInimigo(Entidade* ent1, Entidade* ent2) {
    if (ent1->getId() == ID::jogador || ent1->getId() == ID::jogador2) {
        ent2->setAparece(false);
        ent2->setVelocidade(sf::Vector2f(0.0f, 0.0f));
        (static_cast<Jogador*>(ent1))->tomaDano(static_cast<Projetil*>(ent2)->getDano());
    } else {
        ent1->setAparece(false);
        ent1->setVelocidade(sf::Vector2f(0.0f, 0.0f));
        (static_cast<Jogador*>(ent2))->tomaDano(static_cast<Projetil*>(ent1)->getDano());
    }
}

//ataque corpo a corpo do jogador
void GerenciadorColisao::ataqueJogador(Entidade* ent1, Entidade* ent2, float dx, float dy) {
    if (abs(dy) < 100 && abs(dx) < JOGADOR_ATACA) {
        if (dx > 0) {
            if (ent1->getId() == ID::jogador && (static_cast<Personagem*>(ent1))->getTaAtacando() && !ent1->olhandoEsquerda()) {
                (static_cast<Personagem*>(ent2))->tomaDano(JOGADOR_DANO);
                if ((static_cast<Personagem*>(ent2))->getVida() <= 0)

                    (*(static_cast<Jogador*>(ent1)) += 100);
            } else if (ent2->getId() == ID::jogador && (static_cast<Personagem*>(ent2))->getTaAtacando() && ent2->olhandoEsquerda()) {
                (static_cast<Personagem*>(ent1))->tomaDano(JOGADOR_DANO);
                if ((static_cast<Personagem*>(ent1))->getVida() <= 0)

                    (*(static_cast<Jogador*>(ent2)) += 100);
            }
        } else {
            if (ent1->getId() == ID::jogador && (static_cast<Personagem*>(ent1))->getTaAtacando() && ent1->olhandoEsquerda()) {
                (static_cast<Personagem*>(ent2))->tomaDano(JOGADOR_DANO);
                if ((static_cast<Personagem*>(ent2))->getVida() <= 0)

                    (*(static_cast<Jogador*>(ent1)) += 100);
            } else if (ent2->getId() == ID::jogador && (static_cast<Personagem*>(ent2))->getTaAtacando() && !ent2->olhandoEsquerda()) {
                (static_cast<Personagem*>(ent1))->tomaDano(JOGADOR_DANO);
                if ((static_cast<Personagem*>(ent1))->getVida() <= 0)

                    (*(static_cast<Jogador*>(ent1)) += 100);
            }
        }
    }
}

//funcao para colidir plataforma com outras entidades
void GerenciadorColisao::colidirPlataforma(Entidade* ent1, Entidade* ent2, float dx, float dy, float intersectaX, float intersectaY) {
    switch (ent2->getId()) {

    case ID::jogador:
        if (intersectaX > intersectaY) {
            andaX(ent1, ent2, intersectaX);

        } else {
            if (ent1->getId() == ID::plataforma) {
                if (dy < 0.0f) {
                    andaY(ent1, ent2, intersectaY);
                    (static_cast<Jogador*>(ent2))->setPulo(true);
                } else {
                    andaY(ent1, ent2, intersectaY);
                }
            }
        }
        break;
    case ID::jogador2:
        if (intersectaX > intersectaY) {
            andaX(ent1, ent2, intersectaX);
        } else {
            if (ent1->getId() == ID::plataforma) {
                if (dy < 0.0f) {
                    andaY(ent1, ent2, intersectaY);
                    (static_cast<Jogador*>(ent2))->setPulo(true);
                } else {
                    andaY(ent1, ent2, intersectaY);
                }
            }
        }
        break;
    case ID::mago:
        if (intersectaX > intersectaY) {
            andaX(ent1, ent2, intersectaX);
        } else {
            if (dy > 0.0f) {
                andaY(ent1, ent2, intersectaY);
            } else {
                andaY(ent1, ent2, intersectaY);
            }
        }
        break;
    case ID::ghoul:
        if (intersectaX > intersectaY) {
            andaX(ent1, ent2, intersectaX);
        } else {
            if (dy > 0.0f) {
                andaY(ent1, ent2, intersectaY);
            } else {
                andaY(ent1, ent2, intersectaY);
            }
        }
        break;
    case ID::boss:
        if (intersectaX > intersectaY) {
            andaX(ent1, ent2, intersectaX);
        } else {
            if (dy > 0.0f) {
                andaY(ent1, ent2, intersectaY);
            } else {
                andaY(ent1, ent2, intersectaY);
            }
        }
        break;
    case ID::boladefogo:
        ent2->setAparece(false);
        break;
    case ID::raio:
        ent2->setAparece(false);
        break;
    default:
        break;
    }
}



