#pragma once

#include <string>
#include <vector>

#include "canal.hpp"
#include "canal_texto.hpp"
#include "canal_voz.hpp"

class Servidor{

    // Atributos da classe
    private:
        int usuarioDonoID;
        std::string nome, descricao, codigoConvite;
        std::vector <std::shared_ptr <Canal>> canais;
        std::vector <int> participantesIDs;

    // Métodos da classe
    public:
        Servidor();
        Servidor(int const usuarioDonoID, std::string const nome);

        bool adicionaParticipante(int const usuarioID);

        int getUsuarioDonoID() const;

        void setNome(std::string const nome);
        std::string getNome() const;

        void setDescricao(std::string const descricao);
        std::string getDescricao() const;

        void setCodigoConvite(std::string const nome);
        std::string getCodigoConvite() const;

        std::vector<int> getParticipantesIDs() const;
};
