#pragma once

#include <istream>
#include <ostream>
#include <sstream>

#include "sistema.hpp"

class Executor{
    private:
        Sistema* sistema;
        std::stringstream ss;
        bool sair = false;

    public:
        Executor(Sistema &sistema);

        void iniciar(std::istream &in, std::ostream &out);

        std::string processarLinha(std::string linha);
};