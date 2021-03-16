#include <string>

#include "../include/mensagem.hpp"

// Construtor padrão
Mensagem::Mensagem(){

}

// Construtor sobrecarregado
Mensagem::Mensagem(std::string dataHora, int enviadaPor, std::string conteudo){
    this->dataHora = dataHora;
    this->enviadaPor = enviadaPor;
    this->conteudo = conteudo;
}

// Define a data e hora em que a mensagem foi enviada
void Mensagem::setDataHora(std::string const dataHora){
    this->dataHora = dataHora;
}

// Retorna a data e hora em que a mensagem foi enviada
std::string Mensagem::getDataHora() const{
    return dataHora;
}

// Define o conteúdo da mensagem
void Mensagem::setConteudo(std::string const conteudo){
    this->conteudo = conteudo;
}

// Retorna o conteúdo da mensagem
std::string Mensagem::getConteudo() const{
    return conteudo;
}

// Define o ID do usuário que enviou a mensagem
void Mensagem::setEnviadaPor(int const enviadaPor){
    this->enviadaPor = enviadaPor;
}

// Retorna o ID do usuário que enviou a mensagem
int Mensagem::getEnviadaPor() const{
    return enviadaPor;
}