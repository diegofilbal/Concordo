#pragma once

#include <vector>

#include "../include/canal.hpp"
#include "../include/mensagem.hpp"

class CanalTexto : public Canal{

    // Atributos da classe
    private:
        std::vector <Mensagem> mensagens;

};