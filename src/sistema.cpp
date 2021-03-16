#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

#include "../include/sistema.hpp"
#include "../include/usuario.hpp"

// Vector de usuários do sistema
std::vector <Usuario> usuarios;

Sistema::Sistema(){
    usuarioLogadoId = 0;
}

std::string Sistema::quit(){
    return "Saindo do Concordo...";
}

std::string Sistema::create_user(const std::string email, const std::string senha, const std::string nome){
    
    if(!usuarioLogadoId){ // Verifica se há algum usuário logado
        std::cout << "Criando usuário " << nome << " (" << email << ")" << std::endl;

        for(size_t i = 0; i < usuarios.size(); i++){ // Percorre o vector de usuários
            if(usuarios[i].getEmail() == email){ // Verifica se há algum usuário com o email inserido
                return "Usuário já existe";
            }
        }

        // Cria o novo usuário e insere no vector
        Usuario novo((int) (usuarios.size() + 1), email, senha, nome);
        usuarios.push_back(novo);

        return "Usuário criado";
    }

    return "Operação indisponível! \n Usuário " + usuarios[usuarioLogadoId - 1].getEmail() + " logado!";
}

std::string Sistema::login(const std::string email, const std::string senha){

    if(!usuarioLogadoId){ // Verifica se há algum usuário logado
        for(size_t i = 0; i < usuarios.size(); i++){ // Percorre o vector de usuários
            if(usuarios[i].getEmail() == email){ // Verifica se há algum usuário com o email inserido
                if(usuarios[i].getSenha() == senha){ // Verifica se a senha inserida é correta
                    usuarioLogadoId = usuarios[i].getId(); // Define qual usuário está logado no sistema
                    return "Logado como " + usuarios[i].getEmail();
                }
            }
        }

        return "Senha ou usuário inválidos!";
    }

    return "Operação indisponível! \n Usuário " + usuarios[usuarioLogadoId - 1].getEmail() + " logado!";
}

std::string Sistema::disconnect(){

    if(usuarioLogadoId != 0){ // Verifica se há algum usuário logado
        std::cout << "Desconectando usuário " << usuarios[usuarioLogadoId - 1].getEmail();
        usuarioLogadoId = 0; // Define a variável como 0, significando que não há usuários logados
    }

    return "Não está conectado";
}

std::string Sistema::create_server(const std::string nome){
    return "create_server NÃO IMPLEMENTADO";
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