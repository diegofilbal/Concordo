#include <string>

#include "../include/servidor.hpp"

// Construtor padrão
Servidor::Servidor(){

}

// Construtor sobrecarregado
Servidor::Servidor(int usuarioDonoID, std::string nome){
    this->usuarioDonoID = usuarioDonoID;
    this->nome = nome;
    this->codigoConvite = "";
}

// Retorna o ID do usuário dono do servidor
int Servidor::getUsuarioDonoID(){
    return usuarioDonoID;
}

// Define o nome do servidor
void Servidor::setNome(std::string const nome){
    this->nome = nome;
}

// Retorna o nome do servidor
std::string Servidor::getNome() const{
    return nome;
}

// Define a descrição do servidor
void Servidor::setDescricao(std::string const descricao){
    this->descricao = descricao;
}

// Retorna a descrição do servidor
std::string Servidor::getDescricao() const{
    return descricao;
}

// Define o código de convite
void Servidor::setCodigoConvite(std::string const codigoConvite){
    this->codigoConvite = codigoConvite;
}

// Retorna o código de convite
std::string Servidor::getCodigoConvite() const{
    return codigoConvite;
}