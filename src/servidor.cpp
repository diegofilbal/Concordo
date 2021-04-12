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
void Servidor::enviaMensagem(const std::string nome_canal, const Mensagem mensagem){

    // Procura o canal com o nome escolhido
    auto it_canal = std::find_if(canais.begin(), canais.end(), [nome_canal] (std::shared_ptr <Canal> canal) {
        return canal->getNome() == nome_canal;
    });

    // Envia a mensagem no primeiro canal encontrado com o nome recebido
    (*it_canal)->enviaMensagem(mensagem);
}

// Retorna um vector de mensagens
std::vector <Mensagem> Servidor::listaMensagens(const std::string nome_canal){

    // Procura o canal com o nome escolhido
    auto it_canal = std::find_if(canais.begin(), canais.end(), [nome_canal](std::shared_ptr<Canal> canal) {
        return canal->getNome() == nome_canal;
    });

    // Retorna o vector recebido pelo método listaMensagens() da classe canal
    return (*it_canal)->listaMensagens();
}

// Retorna um vector com o nome dos canais de texto
std::vector <std::string> Servidor::getCanaisTexto() const {

    // Vector para armazenar o nome dos canais de texto do servidor
    std::vector <std::string> nomes_texto;

    // Percorre o vector de canais
    for(auto it_canal = canais.begin(); it_canal != canais.end(); it_canal++){

        // Verifica se o canal atual é do tipo texto para adicioná-lo ao vector a ser retornado
        if(std::dynamic_pointer_cast <CanalTexto> (*it_canal))
            nomes_texto.push_back((*it_canal)->getNome());
    }

    return nomes_texto;
}

// Retorna um vector com o nome dos canais de voz do servidor
std::vector <std::string> Servidor::getCanaisVoz() const {

    // Variável para armazenar no nome dos canais de texto
    std::vector <std::string> nomes_voz;

    // Percorre o vector de canais
    for(auto it_canal = canais.begin(); it_canal != canais.end(); it_canal++){
        
        // Verifica se o canal atual é do tipo voz para adicioná-lo ao vector a ser retornado
        if(std::dynamic_pointer_cast <CanalVoz> (*it_canal))
            nomes_voz.push_back((*it_canal)->getNome());
    }

    return nomes_voz;
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