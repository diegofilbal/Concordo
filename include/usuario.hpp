#pragma once

#include <string>

class Usuario{

    // Atributos da classe
    private:
        // Armazena o ID do usuário
        int id;

        // Armazena o nome do usuário
        std::string nome;

        // Armazena o email do usuário
        std::string email;
        
        // Armazena a senha do usuário
        std::string senha;

    // Métodos da classe
    public:
        // Construtor
        Usuario();

        // Construtor sobrecarregado
        Usuario(int id, std::string email, std::string senha, std::string nome);

        // Retrona o ID do usuário
        int getId() const;

        // Define o nome do usuário
        void setNome(std::string const nome);

        // Retorna o nome do usuário
        std::string getNome() const;

        // Define o email do usuário
        void setEmail(std::string const email);

        // Retorna o email do usuário
        std::string getEmail() const;

        // Define a senha do usuário
        void setSenha(std::string const senha);

        // Retorna a senha do usuário
        std::string getSenha() const;
};