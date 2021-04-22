#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

#include "../include/canal.hpp"
#include "../include/servidor.hpp"
#include "../include/mensagem.hpp"

// Construtor padrão
Servidor::Servidor(){

}

// Construtor sobrecarregado
Servidor::Servidor(int const usuarioDonoID, std::string const nome){
    this->usuarioDonoID = usuarioDonoID;
    this->nome = nome;
    this->codigoConvite = "";
}

// Insere um usuário na lista de participantes do servidor
bool Servidor::adicionaParticipante(int const usuarioID){

    // Iterator de vector de IDs
    std::vector<int>::iterator it_participantesIDs;

    // Procura um usuário com o ID recebido no vector de participantes
    it_participantesIDs = std::find(participantesIDs.begin(), participantesIDs.end(), usuarioID);

    // Verifica se o ID não foi encontrado no vector de participantes
    if(it_participantesIDs == participantesIDs.end()){

        // Insere o número 
        participantesIDs.push_back(usuarioID);

        // Retorna código de sucesso
        return true;
    
    }else{
        // Retorna código de erro
        return false;
    }
}

// Insere o canal recebido no parâmetro no vector de canais do servidor
bool Servidor::criaCanal(std::shared_ptr <Canal> canal){

    // Verifica se o ponteiro não é nulo
    if(canal != nullptr){

        // Insere o canal recebido no vector de canais do servidor
        canais.push_back(canal);

        // Retorna código de sucesso
        return true;

    }else{

        // Retorna código de erro
        return false;
    }
}

// Envia uma mensagem no canal desejado
void Servidor::enviaMensagem(const int id, const Mensagem mensagem){

    // Procura o canal com o ID recebido
    auto it_canal = std::find_if(canais.begin(), canais.end(), [id] (std::shared_ptr <Canal> canal) {
        return canal->getID() == id;
    });

    // Envia a mensagem no canal
    (*it_canal)->enviaMensagem(mensagem);
}

// Retorna as mensagens do canal desejado
std::vector <Mensagem> Servidor::listaMensagens(const int id) const{

    // Procura o canal com o ID recebido
    auto it_canal = std::find_if(canais.begin(), canais.end(), [id](std::shared_ptr<Canal> canal) {
        return canal->getID() == id;
    });

    // Retorna o vector de mensagens do canal encontrado
    return (*it_canal)->listaMensagens();
}

// Retorna o número de canais do servidor
int Servidor::qtdCanais() const{

    // Retorna o tamaho do vector de canais do servidor
    return canais.size();
}

// Retorna um vector de ponteiros de todos os canais do servidor
std::vector <std::shared_ptr <Canal>> Servidor::getCanais() const {

    // Retorna o atributo canais
    return canais;
}

// Retorna um vector com os canais de texto do servidor
std::vector<CanalTexto> Servidor::getCanaisTexto() const {

    // Vector cópia para armazenar os canais de texto do servidor
    std::vector <CanalTexto> copia;

    // Percorre todos os canais do servidor
    for(auto it_canal = canais.begin(); it_canal != canais.end(); ++it_canal) {

        // Verifica se o canal atual é do tipo texto
        if(std::dynamic_pointer_cast <CanalTexto> (*it_canal)){

            // Cria um canal cópia com o mesmo ID e nome do canal de texto atual
            CanalTexto canal((*it_canal)->getID(), (*it_canal)->getNome());

            // Adiciona o canal cópia ao vector a ser retornado
            copia.push_back(canal);
        }
    }

    return copia;
}

// Retorna um vector com os canais de voz do servidor
std::vector <CanalVoz> Servidor::getCanaisVoz() const {
    
    // Vector cópia para armazenar os canais de voz do servidor
    std::vector <CanalVoz> copia;

    // Percorre todos os canais do servidor
    for(auto it_canal = canais.begin(); it_canal != canais.end(); ++it_canal) {
        
        // Verifica se o canal atual é do tipo voz
        if(std::dynamic_pointer_cast <CanalVoz> (*it_canal)){

            // Cria um canal cópia com o mesmo ID e nome do canal de voz atual
            CanalVoz canal((*it_canal)->getID(), (*it_canal)->getNome());

            // Adiciona o canal cópia ao vector a ser retornado
            copia.push_back(canal);
        }
    }

    return copia;
}

// Retorna o nome do canal de acordo com o ID recebido
std::string Servidor::getNomeCanal(int const id) const{
    
    // Busca o canal com o ID recebido
    auto it_canal = std::find_if(canais.begin(), canais.end(), [id](std::shared_ptr<Canal> canal){
        return canal->getID() == id;
    });

    // Retorna o nome do canal encontrado
    return (*it_canal)->getNome();
}

// Retorna o ID do usuário dono do servidor
int Servidor::getUsuarioDonoID() const{
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

// Retorna o vector de IDs dos participantes
std::vector<int> Servidor::getParticipantesIDs() const{
    return participantesIDs;
}