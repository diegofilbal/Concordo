#pragma once

#include <string>

class Usuario{

    // Atributos da classe
    private:
        int id;
        std::string nome, email, senha;

    // Métodos da classe
    public:

        Usuario();
        Usuario(int id, std::string email, std::string senha, std::string nome);
        ~Usuario();

        int getId() const;

        void setNome(std::string const nome);
        std::string getNome() const;

        void setEmail(std::string const email);
        std::string getEmail() const;

        void setSenha(std::string const senha);
        std::string getSenha() const;

};