#pragma once

#include "EntidadeLista.hpp"
#include "Jogador.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include "stdafx.h"

#define FONT_PATH "./imagens/fonte/04B_30__.ttf"



        class GerenciadorGrafico{
        private:
            sf::RenderWindow* window;
            sf::View view;
            sf::Font* fonte;

            //a construtor privada faz parte do padrao de projeto singleton
            static GerenciadorGrafico* pGrafico;
            GerenciadorGrafico();
            std::map<const char*, sf::Texture*> mapaTextura;
        public:
            ~GerenciadorGrafico();
            static GerenciadorGrafico* getGerenciadorGrafico();
            sf::RenderWindow* getWindow();
            void clear();
            void desenhaElemento(sf::RectangleShape* corpo);
            void desenhaElemento(sf::Text* texto);
            void display();
            sf::Texture* carregarTextura(const char* caminho);
            void fecharJanela();
            void centerView(sf::Vector2f pos);
            sf::Vector2u getWindowSize() const;
            sf::Font* getFont();
            const bool verificaJanelaAberta();
            void redefinirTamanhoJanela();
            void apagarTodasTexturas();

        };


