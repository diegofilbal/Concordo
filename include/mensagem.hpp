#pragma once

#include <string>

class Mensagem{

    // Atributos da classe
    private:
        std::string dataHora, conteudo;
        int enviadaPor;
    
    // Métodos da classe
    public:
        Mensagem();
        Mensagem(std::string dataHora, int enviadaPor, std::string conteudo);

        void setDataHora(std::string const dataHora);
        std::string getDataHora() const;

        void setConteudo(std::string const conteudo);
        std::string getConteudo() const;

        void setEnviadaPor(int const enviadaPor);
        int getEnviadaPor() const;
};