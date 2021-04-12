#pragma once

#include <string>
#include <vector>

#include "../include/canal.hpp"
#include "../include/mensagem.hpp"

class CanalTexto : public Canal{

    // Atributos da classe
    private:
        // Armazena todas as mensagens do canal de texto
        std::vector <Mensagem> mensagens;

    // Métodos da classe
    public:
        // Construtor 
        CanalTexto();

        // Construtor sobrecarregado
        CanalTexto(std::string const nome);

        // Envia uma mensagem no canal de texto
        virtual void enviaMensagem(const Mensagem mensagem);

        // Retorna o vector de mensagens do canal
        std::vector <Mensagem> listaMensagens() const;
};