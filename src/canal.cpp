#include <string>

#include "../include/canal.hpp"

// Define o nome do canal
void Canal::setNome(std::string const nome){
    this->nome = nome;
}

// Retorna o nome do canal
std::string Canal::getNome() const{
    return nome;
}