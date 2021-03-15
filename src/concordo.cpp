#include <iostream>
#include <list>
#include <vector>
#include <string>

#include "../include/sistema.h"
#include "../include/executor.h"

using namespace std;

int main(){

    // Inicialização do sistema
    Sistema sistema;
    Executor executor(sistema);

    // O executor recebe o cin e o cout. Ele irá utilizá-los para ler as linhas
    // de comando, executar o método correto em "sistema" e exibir as mensagens
    executor.iniciar(cin, cout);

    return 0;
}