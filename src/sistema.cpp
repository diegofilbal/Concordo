#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

#include "../include/sistema.hpp"
#include "../include/usuario.hpp"
#include "../include/servidor.hpp"

Sistema::Sistema(){
    usuarioLogadoId = 0;
    nomeServidorConectado = "";
    nomeCanalConectado = "";
}

std::string Sistema::quit(){
    return "Saindo do Concordo...";
}

std::string Sistema::create_user(const std::string email, const std::string senha, const std::string nome){
    
    // Verifica se nehnum usuário está logado
    if(!usuarioLogadoId){
        std::cout << "Criando usuário " << nome << " (" << email << ")" << std::endl;

        // Iterator de vector de usuários
        std::vector<Usuario>::iterator it_usuario;

        // Procura algum usuário com o email inserido
        it_usuario = std::find_if(usuarios.begin(), usuarios.end(), [email](Usuario usuario){
            return usuario.getEmail() == email;
        });

        // Verifica se a busca do find_if retornou algum usuário
        if(it_usuario != usuarios.end()){
            return "Usuário já existe!";
        }

        // Cria o novo usuário e insere no vector
        Usuario novo_usuario((int) (usuarios.size() + 1), email, senha, nome);
        usuarios.push_back(novo_usuario);

        return "Usuário criado!";
    }

    return "Operação indisponível! Usuário " + usuarios[usuarioLogadoId - 1].getEmail() + " conectado!";
}

std::string Sistema::login(const std::string email, const std::string senha){

    // Verifica se nenhum usuário está logado
    if(!usuarioLogadoId){

        // Iterator de vector de usuários
        std::vector<Usuario>::iterator it_usuario;

        // Procura algum usuário com o email e senha inseridos
        it_usuario = std::find_if(usuarios.begin(), usuarios.end(), [email, senha](Usuario usuario) {
            return usuario.getEmail() == email && usuario.getSenha() == senha;
        });

        // Verifica se a busca foi bem sucedida
        if(it_usuario != usuarios.end()){

            // Define qual usuário está logado no sistema
            usuarioLogadoId = it_usuario->getId();
            return "Logado como " + it_usuario->getEmail() + "!";
        }

        return "Senha ou usuário inválidos!";
    }

    return "Operação indisponível! Usuário " + usuarios[usuarioLogadoId - 1].getEmail() + " conectado!";
}

std::string Sistema::disconnect(){

    if(usuarioLogadoId != 0){ // Verifica algum usuário está logado
        std::cout << "Desconectando usuário " << usuarios[usuarioLogadoId - 1].getEmail();
        usuarioLogadoId = 0; // Define a variável como 0, significando que não há usuários logados
    }

    return "Não está conectado!";
}

std::string Sistema::create_server(const std::string nome){

    if(usuarioLogadoId != 0){ // Verifica se há algum usuário logado

        for(size_t i = 0; i < servidores.size(); i++){ // Percorre o vector de servidores
            if(servidores[i].getNome() == nome){ // Verifica se já existe um servidor com o nome inserido
                return "Servidor com esse nome já existe!";
            }            
        }

        // Cria novo servidor e insere no vector
        Servidor novo_servidor(usuarioLogadoId, nome);
        servidores.push_back(novo_servidor);

        return "Servidor criado!";
    }

    return "Não está conectado!";
}

std::string Sistema::set_server_desc(const std::string nome, const std::string descricao){
    return "set_server_desc NÃO IMPLEMENTADO";
}

std::string Sistema::set_server_invite_code(const std::string nome, const std::string codigo){
    return "set_server_invite_code NÃO IMPLEMENTADO";
}

std::string Sistema::list_servers(){
    return "list_servers NÃO IMPLEMENTADO";
}

std::string Sistema::remove_server(const std::string nome){
    return "remove_server NÃO IMPLEMENTADO";
}

std::string Sistema::enter_server(const std::string nome, const std::string codigo){
    return "enter_server NÃO IMPLEMENTADO";
}

std::string Sistema::leave_server(){
    return "leave_server NÃO IMPLEMENTADO";
}

std::string Sistema::list_participants(){
    return "list_participants NÃO IMPLEMENTADO";
}

std::string Sistema::list_channels(){
    return "list_channels NÃO IMPLEMENTADO";
}

std::string Sistema::create_channel(const std::string nome, const std::string tipo){
    return "create_channel NÃO IMPLEMENTADO";
}

std::string Sistema::enter_channel(const std::string nome){
    return "enter_channel NÃO IMPLEMENTADO";
}

std::string Sistema::leave_channel(){
    return "leave_channel NÃO IMPLEMENTADO";
}

std::string Sistema::send_message(const std::string mensagem){
    return "send_message NÃO IMPLEMENTADO";
}

std::string Sistema::list_messages(){
    return "list_messages NÃO IMPLEMENTADO";
}