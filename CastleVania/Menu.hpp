#pragma once

#include "PlanoDeFundo.hpp"
#include "Botao.hpp"
#include "ControleMenu.hpp"
#include <vector>

class GerenciadorGrafico;

class Menu {
protected:
    std::vector<Botao*> vectorBotao;
    std::vector<Botao*>::iterator it;
    int selecionado;
    int min;
    int max;
    ControleMenu controle;
    PlanoDeFundo back;
    bool ativo;

public:
    Menu(GerenciadorInput* GI, const char* planoPath);
    virtual ~Menu();

    virtual void exec() = 0;
    void atualizaView();
    void selecionaBaixo();
    void selecionaCima();
};
