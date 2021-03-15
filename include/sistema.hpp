#pragma once

#include <string>
#include <iostream>

// Sistema deve concentrar todas as operações do Concordo
class Sistema{
    private:
        // Precisa guardar uma coleção de servidores;
        // Precisa guardar uma coleção de usuários;
        int usuarioLogadoId; // se 0: não logado, caso contrário guarda o id do usuário logado
        std::string nomeServidorConectado;
        std::string nomeCanalConectado;

    public:
        std::string quit();
        std::string create_user(const std::string email, const std::string senha, const std::string nome);
        std::string login(const std::string email, const std::string senha);
        std::string disconnect();
        std::string create_server(const std::string nome);
        std::string set_server_desc(const std::string nome, const std::string descricao);
        std::string set_server_invite_code(const std::string nome, const std::string codigo);
        std::string list_servers();
        std::string remove_server(const std::string nome);
        std::string enter_server(const std::string nome, const std::string codigo);
        std::string leave_server();
        std::string list_participants();
        std::string list_channels();
        std::string create_channel(const std::string nome, const std::string tipo);
        std::string enter_channel(const std::string nome);
        std::string leave_channel();
        std::string send_message(const std::string mensagem);
        std::string list_messages();
};
