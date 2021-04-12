#pragma once

#include <string>

#include "../include/canal.hpp"
#include "../include/mensagem.hpp"

class CanalVoz : public Canal{

    // Atributos da classe
    private:
        Mensagem ultimaMensagem;

    // Métodos da classe
    public:
        CanalVoz();
        CanalVoz(std::string const nome);
        virtual void enviaMensagem(const Mensagem mensagem);
};