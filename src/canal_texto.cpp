#include <string>
#include <vector>

#include "../include/canal.hpp"
#include "../include/canal_texto.hpp"
#include "../include/mensagem.hpp"

// Construtor
CanalTexto::CanalTexto(){

}

// Construtor sobrecarregado
CanalTexto::CanalTexto(std::string const nome) : Canal(nome){

}

// Envia uma mensagem no canal de texto
void CanalTexto::enviaMensagem(const Mensagem mensagem){

    // Insere a mensagem recebida ao vector de mensagens do canal de texto
    mensagens.push_back(mensagem);
}

// Retorna o vector de mensagens do canal
std::vector <Mensagem> CanalTexto::listaMensagens() const{
    // Retorna o vector de mensagens do canal
    return mensagens;
}