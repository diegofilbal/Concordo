#pragma once

#include <string>

class Mensagem{

    // Atributos da classe
    private:
        // Armazena data e hora de envio
        std::string dataHora;

        // Armazena o conteúdo da mensagem
        std::string conteudo;

        // Armazena o ID do usuário remetente
        int enviadaPor;
    
    // Métodos da classe
    public:
        // Construtor
        Mensagem();

        // Construtor sobrecarregado
        Mensagem(std::string dataHora, int enviadaPor, std::string conteudo);

        // Define a data e hora em que a mensagem foi enviada
        void setDataHora(std::string const dataHora);

        // Retorna a data e hora em que a mensagem foi enviada
        std::string getDataHora() const;

        // Define o conteúdo da mensagem
        void setConteudo(std::string const conteudo);

        // Retorna o conteúdo da mensagem
        std::string getConteudo() const;

        // Define o ID do usuário que enviou a mensagem
        void setEnviadaPor(int const enviadaPor);

        // Retorna o ID do usuário que enviou a mensagem
        int getEnviadaPor() const;
};