#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

#include "../include/sistema.hpp"

/* COMANDOS */
std::string Sistema::quit() {
    return "Saindo do Concordo...";
}

std::string Sistema::create_user(const std::string email, const std::string senha, const std::string nome){
    return "create_user NÃO IMPLEMENTADO";
}

std::string Sistema::login(const std::string email, const std::string senha){
    return "login NÃO IMPLEMENTADO";
}

std::string Sistema::disconnect(){
    return "disconnect NÃO IMPLEMENTADO";
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