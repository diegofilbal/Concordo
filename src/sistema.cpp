#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

#include "../include/sistema.hpp"
#include "../include/usuario.hpp"
#include "../include/servidor.hpp"

// Construtor
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

    // Verifica algum usuário está logado
    if(usuarioLogadoId){
        
        // Guarda o retorno da função em uma string
        std::string retorno = "Desconectando usuário " + usuarios[usuarioLogadoId - 1].getEmail();

        // Define a variável como 0, determinando que não há usuários logados
        usuarioLogadoId = 0;

        return retorno;
    }

    return "Não está conectado!";
}

std::string Sistema::create_server(const std::string nome){

    // Verifica se há algum usuário logado
    if(usuarioLogadoId){

        // Iterator de vector de servidores
        std::vector<Servidor>::iterator it_servidor;

        // Procura algum servidor com o nome inserido
        it_servidor = std::find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor){
            return servidor.getNome() == nome;
        });

        // Verifica se a busca do find_if retornou algum servidor
        if(it_servidor != servidores.end()){
            return "Servidor com esse nome já existe!";
        }

        // Cria novo servidor e insere no vector
        Servidor novo_servidor(usuarioLogadoId, nome);
        servidores.push_back(novo_servidor);

        return "Servidor criado!";
    }

    return "Não está conectado!";
}

std::string Sistema::set_server_desc(const std::string nome, const std::string descricao){

    // Verifica se há algum usuário conectado
    if(usuarioLogadoId){

        // Iterator de vector de servidores
        std::vector<Servidor>::iterator it_servidor;

        // Procura algum servidor com o nome inserido
        it_servidor = std::find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor){
            return servidor.getNome() == nome;
        });

        // Verifica se a busca do find_if retornou algum servidor válido
        if(it_servidor != servidores.end()){
            
            // Verifica se o usuário que solicitou a mudança é dono do servidor
            if(it_servidor->getUsuarioDonoID() == usuarioLogadoId){

                // Altera a descrição do servidor
                it_servidor->setDescricao(descricao);
                return "Descrição do servidor \'" + nome + "\' modificada!";

            }else{
                return "Você não pode alterar a descrição de um servidor que não foi criado por você!";
            }

        }else{
            return "Servidor \'" + nome + "\' não existe!";
        }
    }

    return "Não está conectado!";
}

std::string Sistema::set_server_invite_code(const std::string nome, const std::string codigo){

    // Verifica se há algum usuário conectado
    if(usuarioLogadoId){

        // Iterator de vector de servidores
        std::vector<Servidor>::iterator it_servidor;

        // Procura algum servidor com o nome inserido
        it_servidor = std::find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor){
            return servidor.getNome() == nome;
        });

        // Verifica se a busca do find_if retornou algum servidor válido
        if(it_servidor != servidores.end()){
            
            // Verifica se o usuário que solicitou a mudança é dono do servidor
            if(it_servidor->getUsuarioDonoID() == usuarioLogadoId){

                // Atualiza o código de convite do servidor
                it_servidor->setCodigoConvite(codigo);

                // Verifica se o código inserido era vazio
                if(codigo.empty()){
                    return "Código de convite do servidor \'" + it_servidor->getNome() + "\' removido!";
                }else{
                    return "Código de convite do servidor \'" + it_servidor->getNome() + "\' modificado!";
                }

            }else{
                return "Você não pode alterar o código de convite de um servidor que não foi criado por você!";
            }

        }else{
            return "Servidor \'" + nome + "\' não existe!";
        }
    }

    return "Não está conectado!";
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