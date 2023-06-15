#include "Animacao.hpp"

#include <math.h>


const float Animacao::mudarTempo = 0.2;

Animacao::Animacao() :
pGerenciadorG(GerenciadorGrafico::getGerenciadorGrafico()),
numeroImagem(sf::Vector2u(0, 0)),
textura(NULL),
imagemAtual(sf::Vector2u(0, 0)) {
    tempoTotal = 0.0f;
}

Animacao::~Animacao() {
}

/* Inicializa a animacao. Preciso do caminho para o arquivo, o Id da entidade e o numeroImagem(x,y) da spritesheet  */
void Animacao::inicializarTextura(const char* caminho,sf::Vector2u numeroImagem) {

    this->numeroImagem = numeroImagem;
    textura = pGerenciadorG->carregarTextura(caminho);

    if (textura == NULL) {
        cout << "ERROR: falha em inicilizar textura em inicializarTextura" << endl;
        exit(1);
    }

    uvRect.width = textura->getSize().x / float(numeroImagem.x);
    uvRect.height = textura->getSize().y / float(numeroImagem.y);

    corpo.setSize(sf::Vector2f(uvRect.width, uvRect.height));
    corpo.setOrigin(sf::Vector2f(uvRect.width, uvRect.height) / 2.0f);
    corpo.setTexture(textura);
}
/* baseado nisto --> https://www.youtube.com/watch?v=Aa8bXSq5LDE&t=196s */
/* Atualiza a animacao e a posicao  */
void Animacao::atualiza(int fileira, float dt, bool olhandoEsquerda, sf::Vector2f posicao) {
    if (imagemAtual.y != abs(fileira))
        imagemAtual.x = 0;
    imagemAtual.y = fileira;

    tempoTotal += dt;

    if (tempoTotal >= mudarTempo) {
        tempoTotal -= mudarTempo;
        imagemAtual.x++;

        if (imagemAtual.x >= numeroImagem.x) {
            imagemAtual.x = 0;
        }
    }
    uvRect.top = imagemAtual.y * uvRect.height;

    if (olhandoEsquerda) {
        uvRect.left = (imagemAtual.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    } else {
        uvRect.left = imagemAtual.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }

    corpo.setPosition(posicao);
    corpo.setTextureRect(uvRect);
}

/* seta o numero de imagens da spritesheet */
void Animacao::setnumeroImagem(const sf::Vector2u numeroImagem) {
    this->numeroImagem = numeroImagem;
     }

void Animacao::renderiza() {
    pGerenciadorG->desenhaElemento(&corpo);
      }

