#pragma once

#include <string>
#include <vector>

#include "../include/canal.hpp"
#include "../include/mensagem.hpp"

class CanalTexto : public Canal{

    // Atributos da classe
    private:
        std::vector <Mensagem> mensagens;

    // Métodos da classe
    public:
        CanalTexto();
        CanalTexto(std::string const nome);
        virtual void enviaMensagem(const Mensagem mensagem);
};