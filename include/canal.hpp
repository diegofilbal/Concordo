#pragma once

#include <string>

class Canal{

    // Atributos da classe
    protected:
        std::string nome;

    // Métodos da classe
    public:
        virtual void setNome(std::string const nome);
        virtual std::string getNome() const;

};