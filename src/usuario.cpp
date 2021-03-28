#include <string>

#include "../include/usuario.hpp"

// Construtor padrão
Usuario::Usuario(){

}

// Construtor sobrecarregado
Usuario::Usuario(int id, std::string email, std::string senha, std::string nome){ 
    // Define o valor dos atributos 
    this->id = id;
    this->email = email;
    this->senha = senha;
    this->nome = nome;
}

// Retrona o ID do usuário
int Usuario::getId() const{
    return id;
}

// Define o nome do usuário
void Usuario::setNome(std::string const nome){
    this->nome = nome;
}

// Retorna o nome do usuário
std::string Usuario::getNome() const{
    return nome;
}

// Define o email do usuário
void Usuario::setEmail(std::string const email){
    this->email = email;
}

// Retorna o email do usuário
std::string Usuario::getEmail() const{
    return email;
}

// Define a senha do usuário
void Usuario::setSenha(std::string const senha){
    this->senha = senha;
}

// Retorna a senha do usuário
std::string Usuario::getSenha() const{
    return senha;
}
