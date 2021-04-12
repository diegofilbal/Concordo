#pragma once

#include <string>
#include <vector>

#include "mensagem.hpp"

class Canal{

    // Atributos da classe
    protected:
        std::string nome;

    // Métodos da classe
    public:
        Canal();
        Canal(std::string const nome);
        ~Canal();
        virtual void enviaMensagem(const Mensagem mensagem) = 0;
        virtual std::vector <Mensagem> listaMensagens() const = 0;
        virtual void setNome(std::string const nome);
        virtual std::string getNome() const;

};