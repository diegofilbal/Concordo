#pragma once

#include <string>
#include <iostream>

#include "../include/usuario.hpp"
#include "../include/servidor.hpp"

// Sistema deve concentrar todas as operações do Concordo
class Sistema{
    private:
        // Armazena os usuários cadastrados no sistema
        std::vector <Usuario> usuarios;

        // Armazena os servidores cadastrados no sistema
        std::vector <Servidor> servidores;

        // Armazena o id do usuário conectado
        int usuarioLogadoId;

        // Armazena o nome do servidor conectado
        std::string nomeServidorConectado;

        // Armazena o ID do canal conectado
        int idCanalConectado;

        // Salva os dados dos usuários cadastrados
        void salvarUsuarios() const;

        // Salva os dados dos servidores cadastrados
        void salvarServidores() const;

       public:
        // Construtor
        Sistema();
        
        // Salva todos os dados do sistema
        void salvar() const;

        // Função do comando "quit"
        std::string quit();

        // Função do comando "create-user"
        std::string create_user(const std::string email, const std::string senha, const std::string nome);

        // Função do comando "login"
        std::string login(const std::string email, const std::string senha);

        // Função do comando "disconnect"
        std::string disconnect();

        // Função do comando "create-server"
        std::string create_server(const std::string nome);

        // Função do comando "set-server-desc"
        std::string set_server_desc(const std::string nome, const std::string descricao);

        // Função do comando "set-server-invite-code"
        std::string set_server_invite_code(const std::string nome, const std::string codigo);

        // Função do comando "list-servers"
        std::string list_servers();

        // Função do comando "remove-server"
        std::string remove_server(const std::string nome);

        // Função do comando "enter-server"
        std::string enter_server(const std::string nome, const std::string codigo);

        // Função do comando "leave-server"
        std::string leave_server();

        // Função do comando "list-participants"
        std::string list_participants();

        // Função do comando "list-channels"
        std::string list_channels();

        // Função do comando "create-channel"
        std::string create_channel(const std::string nome, const std::string tipo);

        // Função do comando "enter-channel"
        std::string enter_channel(const std::string nome, const std::string tipo);

        // Função do comando "leave-channel"
        std::string leave_channel();

        // Função do comando "send-message"
        std::string send_message(const std::string mensagem);

        // Função do comando "list-messages"
        std::string list_messages();
};
