#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <stdlib.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;


#include <fstream>



/* =================================================== */
/*                      DEFINE                         */
/* =================================================== */
/*              JANELA E COISAS GRAFICAS               */
/* =================================================== */

#define FRAME_RATE 100
#define WIDTH 1280
#define HEIGHT 720

/* =================================================== */
/*                     INIMIGOS                        */
/* =================================================== */

#define VIDA_INIMIGO 2000
#define DANO_INIMIGO 25
#define VELOCIDADE_INIMIGO_X 300
#define VELOCIDADE_INIMIGO_X_MAX 500
#define VELOCIDADE_INIMIGO_X_MIN 200

/* =================================================== */
/*                       MAGO                          */
/* =================================================== */
#define MAGO_LARGURA 70
#define MAGO_ALTURA 110
/* =================================================== */
/*                      GHOUL                          */
/* =================================================== */
#define GHOUL_LARGURA 100
#define GHOUL_ALTURA 165

/* =================================================== */
/*                      MAPA                           */
/* =================================================== */

#define GRAVIDADE 3000.f
#define DIV0 0.0000001f //garante que a divisao nao e por 0

/* =================================================== */
/*                    PLATAFORMA                       */
/* =================================================== */

#define PLATAFORMA_LARGURA 225
#define PLATAFORMA_ALTURA 100

/* =================================================== */
/*                      PAREDE                         */
/* =================================================== */

#define PAREDE_LARGURA 45
#define PAREDE_ALTURA 45

/* =================================================== */
/*                    BOLA DE FOGO                     */
/* =================================================== */

#define BOLADEFOGO_LARGURA 120
#define BOLADEFOGO_ALTURA 72
#define BOLA_DE_FOGO_VELOCIDADE 400
#define BOLA_DE_FOGO_ALTURAMAX 200

/* =================================================== */
/*                      PROJETIL                       */
/* =================================================== */

#define DANO_PROJETIL 50

/* =================================================== */
/*                      ESPINHO                        */
/* =================================================== */

#define DANO_ESPINHO 5
#define ESPINHO_LARGURA 225
#define ESPINHO_ALTURA 45

/* =================================================== */
/*                      RAIO                           */
/* =================================================== */
#define VELOCIDADE_RAIO 500
#define RAIO_ALTURAMAX 300
/* =================================================== */
/*                      TEIA                           */
/* =================================================== */

#define TEIA_LARGURA 225
#define TEIA_ALTURA 45


