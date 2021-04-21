#include <string>

#include "../include/canal.hpp"

// Construtor padrão
Canal::Canal(){

}

// Construtor sobrecarregado
Canal::Canal(int const id, std::string const nome) {
    this->id = id;
    this->nome = nome;
}

// Destrutor
Canal::~Canal(){

}

// Define o ID do canal
void Canal::setID(int const id) {
    this->id = id;
}

// Retorna o nome do canal
int Canal::getID() const {
    return id;
}

// Define o nome do canal
void Canal::setNome(std::string const nome){
    this->nome = nome;
}

// Retorna o nome do canal
std::string Canal::getNome() const{
    return nome;
}