#pragma once

#include <string>

class Canal{

    // Atributos da classe
    protected:
        std::string nome;

    // Métodos da classe
    public:
        void setNome(std::string const nome);
        std::string getNome() const;

};