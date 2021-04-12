#pragma once

#include <memory>
#include <string>
#include <vector>

#include "canal.hpp"
#include "canal_texto.hpp"
#include "canal_voz.hpp"

class Servidor{

    // Atributos da classe
    private:
        // Armazena o ID do usuário dono
        int usuarioDonoID;

        // Armazena o nome do servidor
        std::string nome;

        // Armazena a descrição do servidor
        std::string descricao;

        // Armazena o código de convite do servidor
        std::string codigoConvite;

        // Armazena os canais do servidor
        std::vector <std::shared_ptr <Canal>> canais;

        // Armazena os IDs dos usuários membros do servidor
        std::vector <int> participantesIDs;

    // Métodos da classe
    public:
        // Construtor
        Servidor();

        // Construtor sobrecarregado
        Servidor(int const usuarioDonoID, std::string const nome);

        // Insere um usuário na lista de participantes do servidor
        bool adicionaParticipante(int const usuarioID);

        // Insere o canal recebido no parâmetro no vector de canais do servidor
        bool criaCanal(std::shared_ptr <Canal> const canal);

        // Envia uma mensagem no canal desejado
        void enviaMensagem(const std::string nome_canal, const Mensagem mensagem);

        // Retorna um vector de mensagens
        std::vector <Mensagem> listaMensagens(const std::string nome_canal);

        // Retorna um vector com o nome dos canais de texto
        std::vector <std::string> getCanaisTexto() const;

        // Retorna um vector com o nome dos canais de voz do servidor
        std::vector <std::string> getCanaisVoz() const;

        // Retorna o ID do usuário dono do servidor
        int getUsuarioDonoID() const;

        // Define o nome do servidor
        void setNome(std::string const nome);

        // Retorna o nome do servidor
        std::string getNome() const;

        // Define a descrição do servidor
        void setDescricao(std::string const descricao);

        // Retorna a descrição do servidor
        std::string getDescricao() const;

        // Define o código de convite
        void setCodigoConvite(std::string const nome);

        // Retorna o código de convite
        std::string getCodigoConvite() const;

        // Retorna o vector de IDs dos participantes
        std::vector<int> getParticipantesIDs() const;
};
