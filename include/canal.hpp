#pragma once

#include <string>
#include <vector>

#include "mensagem.hpp"

class Canal{

    // Atributos da classe
    protected:
        // Armazena o nome do canal
        std::string nome;

    // Métodos da classe
    public:
        // Construtor
        Canal();

        // Construtor sobrecarregado
        Canal(std::string const nome);

        // Destrutor
        ~Canal();

        // Envia uma mensagem no canal
        virtual void enviaMensagem(const Mensagem mensagem) = 0;

        // Retorna o vector de mensagens do canal
        virtual std::vector <Mensagem> listaMensagens() const = 0;

        // Define o nome do canal
        virtual void setNome(std::string const nome);

        // Retorna o nome do canal
        virtual std::string getNome() const;
};