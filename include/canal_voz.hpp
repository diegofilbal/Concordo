#pragma once

#include "../include/canal.hpp"
#include "../include/mensagem.hpp"

class CanalVoz : public Canal{

    // Atributos da classe
    private:
        Mensagem ultimaMensagem;

    public:
        CanalVoz();
        CanalVoz(std::string const nome) : Canal(nome){};
};