#pragma once

#include <string>
#include <vector>

#include "../include/canal.hpp"
#include "../include/mensagem.hpp"

class CanalVoz : public Canal{

    // Atributos da classe
    private:
        // Armazena a última mensagem enviada ao canal de voz
        Mensagem ultimaMensagem;

    // Métodos da classe
    public:
        // Construtor
        CanalVoz();

        // Construtor sobrecarregado
        CanalVoz(int const id, std::string const nome);

        // Envia uma mensagem no canal de voz
        virtual void enviaMensagem(const Mensagem mensagem);

        // Retorna um vector de um único elemento contendo a ultima mensagem enviada no canal
        virtual std::vector <Mensagem> listaMensagens() const;
};