#include <string>

#include "../include/canal.hpp"

// Construtor padrão
Canal::Canal(){

}

// Construtor sobrecarregado
Canal::Canal(std::string const nome){
    this->nome = nome;
}

// Destrutor
Canal::~Canal(){

}

// Define o nome do canal
void Canal::setNome(std::string const nome){
    this->nome = nome;
}

// Retorna o nome do canal
std::string Canal::getNome() const{
    return nome;
}