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

std::string Sistema::login(const std::string email, const std::string senha){

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

        // Define que o usuário não está conectado a nenhum servidor
        nomeServidorConectado = "";

        return "Logado como " + it_usuario->getEmail() + "!";
    }

    return "Senha ou usuário inválidos!";
}

std::string Sistema::disconnect(){

    // Verifica algum usuário está logado
    if(usuarioLogadoId){
        
        // Guarda o retorno da função em uma string
        std::string retorno = "Desconectando usuário " + usuarios[usuarioLogadoId - 1].getEmail();

        // Determina que não há usuários conectados a nenhum servidor
        nomeServidorConectado = "";

        // Determina que não há usuários logados no sistema
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

        // Adiciona o dono do servidor à lista de participantes
        servidores.back().adicionaParticipante(usuarioLogadoId);

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

    // Verifica se há algum usuário conectado
    if(usuarioLogadoId){

        // Verifica se o vector de servidores está vazio
        if(servidores.empty()){
            return "Não há servidores cadastrados!";
        }

        // Variável para armezenar o retorno da função
        std::string nome_servidores_retorno = "";

        // Iterator de vector de servidores
        std::vector<Servidor>::iterator it_servidor;

        // Concatena o nome dos servidores na variável de retorno
        for(it_servidor = servidores.begin(); it_servidor != servidores.end(); it_servidor++){
            if(it_servidor != servidores.end() - 1)
                nome_servidores_retorno += it_servidor->getNome() + "\n";
            else
                nome_servidores_retorno += it_servidor->getNome();
        }

        return nome_servidores_retorno;
    }

    return "Não está conectado!";
}

std::string Sistema::remove_server(const std::string nome){
    
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

            // Verifica se o usuário que solicitou a remoção é dono do servidor
            if(it_servidor->getUsuarioDonoID() == usuarioLogadoId){

                // Se o servidor conectado no momento for o mesmo a ser removido, o usuário é desconectado dele antes da remoção
                if(it_servidor->getNome() == nomeServidorConectado)
                    leave_server();

                // Remove o servidor
                servidores.erase(it_servidor);
                return "Servidor \'" + nome + "\' removido!";

            }else{
                return "Você não é dono do servidor \'" + nome + "\'!";
            }

        }else{
            return "Servidor \'" + nome + "\' não existe!";
        }
    }

    return "Não está conectado!";
}

std::string Sistema::enter_server(const std::string nome, const std::string codigo){

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

            // Variável para armazenar retorno da função adicionaParticipante()
            bool retorno;

            // Verifica se o servidor é aberto
            if(it_servidor->getCodigoConvite().empty()){

                // Adiciona o usuário na lista de participantes do servidor
                retorno = it_servidor->adicionaParticipante(usuarioLogadoId);

            }else{

                // Verifca se o usuário que quer entrar é o dono do servidor
                if(it_servidor->getUsuarioDonoID() == usuarioLogadoId){

                    // Adiciona o usuário na lista de participantes do servidor
                    retorno = it_servidor->adicionaParticipante(usuarioLogadoId);

                }else{

                    // Verifica se o código de convite foi inserido
                    if(!codigo.empty()){

                        // Verifica se o código de convite inserido está correto
                        if(it_servidor->getCodigoConvite() == codigo){

                            // Adiciona o usuário na lista de participantes do servidor
                            retorno = it_servidor->adicionaParticipante(usuarioLogadoId);
                        
                        }else{
                            return "Código de convite inválido!";
                        }

                    }else{
                        return "Servidor requer código de convite!";
                    }
                }
            }

            // Define o servidor conectado no momento
            nomeServidorConectado = it_servidor->getNome();

            // Verifica o retorno para saber se o usuário foi inserido ou se já era participante
            if(retorno)
                return "Entrou no servidor com sucesso!";
            else
                return "O usuário já está na lista de participantes do servidor!";

        }else{
            return "Servidor \'" + nome + "\' não existe!";
        }
    }

    return "Não está conectado!";
}

std::string Sistema::leave_server(){

    // Verifica se há algum usuário logado
    if(usuarioLogadoId){

        // Verifica se o usuário já não está conectado a nenhum servidor no momento
        if(nomeServidorConectado.empty()){
            return "Você não está visualizando nenhum servidor!";
        }

        // Variável para guardar a string de retorno da função
        std::string retorno = "Saindo do servidor \'" + nomeServidorConectado + "\'!";

        // Desconecta o usuário do servidor
        nomeServidorConectado = "";

        return retorno;
    }

    return "Não está conectado!";
}

std::string Sistema::list_participants(){
    
    // Verifica se há algum usuário conectado
    if(usuarioLogadoId){

        // Verifica se o usuário não está conectado a nenhum servidor no momento
        if(nomeServidorConectado.empty()){
            return "Não está conectado a nenhum servidor!";
        }

        // Iterator de vetor de servidores
        std::vector<Servidor>::iterator it_servidor;

        // Variável que armazena o nome do servidor conectado no momento
        std::string nome = nomeServidorConectado;

        // Busca o servidor que o usuário está conectado no momento
        it_servidor = std::find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor) {
            return servidor.getNome() == nome;
        });

        // Vector para receber o vector de IDs dos participantes do servidor
        std::vector <int> listaIDs = it_servidor->getParticipantesIDs();

        // Iterator de vector de IDs
        std::vector<int>::iterator it_IDs;

        // String de retorno da função
        std::string retorno = "";

        // Concatena o nome de todos os participantes do servidor na variável de retorno
        for (it_IDs = listaIDs.begin(); it_IDs != listaIDs.end(); it_IDs++){
            if(it_IDs != listaIDs.end() - 1)
                retorno += usuarios[*it_IDs - 1].getNome() + "\n";
            else
                retorno += usuarios[*it_IDs - 1].getNome();
        }

        return retorno;
    }

    return "Não está conectado!";
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