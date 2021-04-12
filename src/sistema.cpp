#include <algorithm>
#include <time.h>
#include <iostream>
#include <vector>

#include "../include/mensagem.hpp"
#include "../include/canal.hpp"
#include "../include/canal_texto.hpp"
#include "../include/canal_voz.hpp"
#include "../include/sistema.hpp"
#include "../include/usuario.hpp"
#include "../include/servidor.hpp"

// Construtor
Sistema::Sistema(){
    // Inicializa os atributos
    usuarioLogadoId = 0;
    nomeServidorConectado = "";
    nomeCanalConectado = "";
}

// Função do comando "quit"
std::string Sistema::quit(){
    return "Saindo do Concordo...";
}

// Função do comando "create-user"
std::string Sistema::create_user(const std::string email, const std::string senha, const std::string nome){
    
    std::cout << "Criando usuário " << nome << " (" << email << ")" << std::endl;

    // Procura algum usuário com o email inserido
    auto it_usuario = std::find_if(usuarios.begin(), usuarios.end(), [email](Usuario usuario){
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

// Função do comando "login"
std::string Sistema::login(const std::string email, const std::string senha){

    // Procura algum usuário com o email e senha inseridos
    auto it_usuario = std::find_if(usuarios.begin(), usuarios.end(), [email, senha](Usuario usuario) {
        return usuario.getEmail() == email && usuario.getSenha() == senha;
    });

    // Verifica se a busca foi bem sucedida
    if(it_usuario != usuarios.end()){

        // Define qual usuário está logado no sistema
        usuarioLogadoId = it_usuario->getId();

        // Define que o usuário não está conectado a nenhum canal
        if(!nomeCanalConectado.empty()) leave_channel();

        // Define que o usuário não está conectado a nenhum servidor
        if(!nomeServidorConectado.empty()) leave_server();

        return "Logado como " + it_usuario->getEmail() + "!";
    }

    return "Senha ou usuário inválidos!";
}

// Função do comando "disconnect"
std::string Sistema::disconnect(){

    // Verifica algum usuário está logado
    if(usuarioLogadoId){
        
        // Guarda o retorno da função em uma string
        std::string retorno = "Desconectando usuário " + usuarios[usuarioLogadoId - 1].getEmail();

        // Define que o usuário não está conectado a nenhum canal
        if(!nomeCanalConectado.empty()) leave_channel();

        // Determina que não há usuários conectados a nenhum servidor
        if(!nomeServidorConectado.empty()) leave_server();

        // Determina que não há usuários logados no sistema
        usuarioLogadoId = 0;

        return retorno;
    }

    return "Não está conectado!";
}

// Função do comando "create-server"
std::string Sistema::create_server(const std::string nome){

    // Verifica se há algum usuário logado
    if(usuarioLogadoId){

        // Verifica se o nome inserido é vazio
        if(nome.empty()){
            return "Não é possível criar um servidor sem nome!";
        }

        // Procura algum servidor com o nome inserido
        auto it_servidor = std::find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor){
            return servidor.getNome() == nome;
        });

        // Verifica se a busca do find_if retornou algum servidor
        if(it_servidor != servidores.end()){
            return "Servidor com esse nome já existe!";
        }

        // Cria novo servidor
        Servidor novo_servidor(usuarioLogadoId, nome);

        // Adiciona o dono do servidor à lista de participantes
        novo_servidor.adicionaParticipante(usuarioLogadoId);

        // Insere o novo servidor no vector de servidores
        servidores.push_back(novo_servidor);

        return "Servidor criado!";
    }

    return "Não está conectado!";
}

// Função do comando "set-server-desc"
std::string Sistema::set_server_desc(const std::string nome, const std::string descricao){

    // Verifica se há algum usuário conectado
    if(usuarioLogadoId){

        // Procura algum servidor com o nome inserido
        auto it_servidor = std::find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor){
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

// Função do comando "set-server-invite-code"
std::string Sistema::set_server_invite_code(const std::string nome, const std::string codigo){

    // Verifica se há algum usuário conectado
    if(usuarioLogadoId){

        // Procura algum servidor com o nome inserido
        auto it_servidor = std::find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor){
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

// Função do comando "list-servers"
std::string Sistema::list_servers(){

    // Verifica se há algum usuário conectado
    if(usuarioLogadoId){

        // Verifica se o vector de servidores está vazio
        if(servidores.empty()){
            return "Não há servidores cadastrados!";
        }

        // Variável para armezenar o retorno da função
        std::string retorno = "";

        // Concatena o nome dos servidores na variável de retorno
        for(auto it_servidor = servidores.begin(); it_servidor != servidores.end(); it_servidor++){
            if(it_servidor != servidores.end() - 1)
                retorno += it_servidor->getNome() + "\n";
            else
                retorno += it_servidor->getNome();
        }

        return retorno;
    }

    return "Não está conectado!";
}

// Função do comando "remove-server"
std::string Sistema::remove_server(const std::string nome){
    
    // Verifica se há algum usuário conectado
    if(usuarioLogadoId){

        // Procura algum servidor com o nome inserido
        auto it_servidor = std::find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor){
            return servidor.getNome() == nome;
        });

        // Verifica se a busca do find_if retornou algum servidor válido
        if(it_servidor != servidores.end()){

            // Verifica se o usuário que solicitou a remoção é dono do servidor
            if(it_servidor->getUsuarioDonoID() == usuarioLogadoId){

                // Se o servidor conectado no momento for o mesmo a ser removido, o usuário é desconectado dele antes da remoção
                if(it_servidor->getNome() == nomeServidorConectado) leave_server();

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

// Função do comando "enter-server"
std::string Sistema::enter_server(const std::string nome, const std::string codigo){

    // Verifica se há algum usuário conectado
    if(usuarioLogadoId){

        // Procura algum servidor com o nome inserido
        auto it_servidor = std::find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor){
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

            // Desconecta os usuário de qualquer canal
            if(!nomeCanalConectado.empty()) leave_channel();

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

// Função do comando "leave-server"
std::string Sistema::leave_server(){

    // Verifica se há algum usuário logado
    if(usuarioLogadoId){

        // Verifica se o usuário já não está conectado a nenhum servidor no momento
        if(nomeServidorConectado.empty()){
            return "Você não está visualizando nenhum servidor!";
        }

        // Variável para guardar a string de retorno da função
        std::string retorno = "Saindo do servidor \'" + nomeServidorConectado + "\'!";

        // Desconecta o usuário do canal
        if(!nomeCanalConectado.empty()) leave_channel();

        // Desconecta o usuário do servidor
        nomeServidorConectado = "";

        return retorno;
    }

    return "Não está conectado!";
}

// Função do comando "list-participants"
std::string Sistema::list_participants(){
    
    // Verifica se há algum usuário conectado
    if(usuarioLogadoId){

        // Verifica se o usuário não está conectado a nenhum servidor no momento
        if(nomeServidorConectado.empty()){
            return "Não está conectado a nenhum servidor!";
        }

        // Variável que armazena o nome do servidor conectado no momento
        std::string nome = nomeServidorConectado;

        // Busca o servidor que o usuário está conectado no momento
        auto it_servidor = std::find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor) {
            return servidor.getNome() == nome;
        });

        // Vector para receber o vector de IDs dos participantes do servidor
        std::vector <int> listaIDs = it_servidor->getParticipantesIDs();

        // String de retorno da função
        std::string retorno = "";

        // Concatena o nome de todos os participantes do servidor na variável de retorno
        for (auto it_IDs = listaIDs.begin(); it_IDs != listaIDs.end(); it_IDs++){
            if(it_IDs != listaIDs.end() - 1)
                retorno += usuarios[*it_IDs - 1].getNome() + "\n";
            else
                retorno += usuarios[*it_IDs - 1].getNome();
        }

        return retorno;
    }

    return "Não está conectado!";
}

// Função do comando "list-channels"
std::string Sistema::list_channels(){

    // Verifica se há algum usuário conectado
    if(usuarioLogadoId) {

        // Verifica se o usuário está conectado a algum servidor
        if(nomeServidorConectado.empty()) {
            return "Não está conectado a nenhum servidor!";
        }

        // Variável que armazena o nome do servidor conectado no momento
        std::string nome = nomeServidorConectado;

        // Busca o servidor que o usuário está conectado no momento
        auto it_servidor = std::find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor) {
            return servidor.getNome() == nome;
        });

        // Recebe a lista de canais de texto do servidor atual
        std::vector <std::string> c_texto = it_servidor->getCanaisTexto();

        // Recebe a lista de canais de voz do servidor atual
        std::vector <std::string> c_voz = it_servidor->getCanaisVoz();

        // Verifica se não há nenhum canal cadastrado
        if(c_texto.empty() && c_voz.empty()){
            return "Nenhum canal no servidor!";
        }
        
        // Variável de retorno para concatenar o nome dos canais
        std::string retorno;

        // Verifica se há canais de texto cadastrados
        if(!c_texto.empty()){
            retorno += "#canais de texto\n";

            // Concatena o nome dos canais de texto à string de retorno
            for(auto it_str = c_texto.begin(); it_str != c_texto.end(); ++it_str){
                if(it_str != c_texto.end() - 1)
                    retorno += *it_str + "\n";
                else
                    retorno += *it_str;
            }
        }

        // Verifica se há canais de voz cadastrados
        if(!c_voz.empty()){

            if(!c_texto.empty()) retorno += "\n";

            retorno += "#canais de voz\n";

            // Concatena o nome dos canais de voz à string de retorno
            for(auto it_str = c_voz.begin(); it_str != c_voz.end(); ++it_str){
                if(it_str != c_voz.end() - 1)
                    retorno += *it_str + "\n";
                else
                    retorno += *it_str;
            }
        }

        return retorno;
    }

    return "Não está conectado!";
}

// Função do comando "create-channel"
std::string Sistema::create_channel(const std::string nome, const std::string tipo){

    // Verifica se há algum usuário conectado
    if(usuarioLogadoId){

        // Verifica se o usuário está conectado a algum servidor
        if(nomeServidorConectado.empty()) {
            return "Não está conectado a nenhum servidor!";
        }

        // Variável que armazena o nome do servidor conectado no momento
        std::string nome_servidor_temp = nomeServidorConectado;

        // Busca o servidor que o usuário está conectado no momento
        auto it_servidor = std::find_if(servidores.begin(), servidores.end(), [nome_servidor_temp](Servidor servidor) {
            return servidor.getNome() == nome_servidor_temp;
        });

        // Verifica o tipo do canal a ser criado
        if(tipo != "texto" && tipo != "voz")
            return "Tipo de canal inválido!";

        if(tipo == "texto"){

            // Recebe a lista de canais de texto do servidor atual
            std::vector <std::string> c_texto = it_servidor->getCanaisTexto();

            // Busca um canal com o mesmo nome
            auto it_str = std::find_if(c_texto.begin(), c_texto.end(), [nome](std::string nome_canal) {
                return nome_canal == nome;
            });

            // Verifica se a busca achou um canal com o mesmo nome
            if(it_str != c_texto.end())
                return "Canal de texto \'" + nome + "\' já existe!";
            
            // Cria o canal de texto
            std::shared_ptr <CanalTexto> novo_canal(new CanalTexto(nome));

            // Insere o canal lista de canais do servidor e guarda o retorno do método
            bool codigo = it_servidor->criaCanal(novo_canal);

            // Verifica se a inserção foi realizada com sucesso
            if(codigo)
                return "Canal de texto \'" + nome + "\' criado!";
            else
                return "Erro inesperado ao criar canal de texto \'" + nome + "\'!";
        
        }else{

            // Recebe a lista de canais de voz do servidor atual
            std::vector <std::string> c_voz = it_servidor->getCanaisVoz();

            // Busca um canal com o mesmo nome
            auto it_str = std::find_if(c_voz.begin(), c_voz.end(), [nome](std::string nome_canal) {
                return nome_canal == nome;
            });

            // Verifica se a busca achou um canal com o mesmo nome
            if(it_str != c_voz.end())
                return "Canal de voz \'" + nome + "\' já existe!";

            // Cria o canal de voz
            std::shared_ptr <CanalVoz> novo_canal(new CanalVoz(nome));

            // Insere o canal lista de canais do servidor e guarda o retorno do método
            bool codigo = it_servidor->criaCanal(novo_canal);

            // Verifica se a inserção foi realizada com sucesso
            if(codigo)
                return "Canal de voz \'" + nome + "\' criado!";
            else
                return "Erro inesperado ao criar canal de voz \'" + nome + "\'!";
        }
    }

    return "Não está conectado!";
}

// Função do comando "enter-channel"
std::string Sistema::enter_channel(const std::string nome, const std::string tipo){

    // Verifica se há algum usuário conectado
    if(usuarioLogadoId){

        // Verifica se o usuário está conectado a algum servidor
        if(nomeServidorConectado.empty()) {
            return "Não está conectado a nenhum servidor!";
        }

        // Variável que armazena o nome do servidor conectado no momento
        std::string nome_servidor_temp = nomeServidorConectado;

        // Busca o servidor que o usuário está conectado no momento
        auto it_servidor = std::find_if(servidores.begin(), servidores.end(), [nome_servidor_temp](Servidor servidor) {
            return servidor.getNome() == nome_servidor_temp;
        });

        // Busca um canal de texto com o mesmo nome no servidor atual
        std::vector <std::string> c_texto = it_servidor->getCanaisTexto();
        auto it_texto = std::find_if(c_texto.begin(), c_texto.end(), [nome](std::string nome_canal) {
            return nome_canal == nome;
        });

        // Busca um canal de voz com o mesmo nome no servidor atual
        std::vector <std::string> c_voz = it_servidor->getCanaisVoz();
        auto it_voz = std::find_if(c_voz.begin(), c_voz.end(), [nome](std::string nome_canal) {
            return nome_canal == nome;
        });

        // Verifica se existem dois canais de tipos diferentes com o mesmo nome recebido
        if(it_texto != c_texto.end() && it_voz != c_voz.end()){

            // Verifica se o tipo informado é inválido
            if(tipo != "texto" && tipo != "voz")
                return "Dois canais de tipos diferentes com o nome \'" + nome + "\' encontrados!\nTente novamente informando um tipo válido!";

            // Conecta o usuário ao canal
            nomeCanalConectado = nome;

            return "Entrou no canal de " + tipo + " \'" + nome + "\'!";
        }

        // Verifica se pelo menos um resultado foi encontrado, seja canal de texto ou de voz
        if(it_texto != c_texto.end() || it_voz != c_voz.end()) {

            // Conecta o usuário ao(s) canais
            nomeCanalConectado = nome;

            return "Entrou no canal \'" + nome + "\'!";
        }
        
        return "Canal \'" + nome + "\' não existe!";
    }

    return "Não está conectado!";
}

// Função do comando "leave-channel"
std::string Sistema::leave_channel(){

    // Verifica se há algum usuário logado
    if(usuarioLogadoId){

        // Verifica se o usuário está conectado a algum servidor
        if(nomeServidorConectado.empty()){
            return "Não está conectado a nenhum servidor!";
        }

        // Verifica se o usuário já não está conectado a nenhum canal no momento
        if(nomeCanalConectado.empty()){
            return "Você não está conectado a nenhum canal!";
        }

        // Variável para guardar a string de retorno da função
        std::string retorno = "Saindo do canal \'" + nomeCanalConectado + "\'!";

        // Desconecta o usuário do canal
        nomeCanalConectado = "";

        return retorno;
    }

    return "Não está conectado!";
}

// Função do comando "send-message"
std::string Sistema::send_message(const std::string mensagem){

    // Verifica se há algum usuário conectado
    if(usuarioLogadoId){

        // Verifica se o usuário está conectado a algum servidor
        if(nomeServidorConectado.empty())
            return "Não está conectado a nenhum servidor!";

        // Verifica se o usuário está conectado a algum canal
        if(nomeCanalConectado.empty())
            return "Não está conectado a nenhum canal!";

        // Verifica se a mensagem está vazia
        if(mensagem.empty()){
            return "Não é possível enviar uma mensagem vazia!";
        }

        // Busca o servidor que o usuário está conectado no momento
        std::string nome_servidor_temp = nomeServidorConectado;
        auto it_servidor = std::find_if(servidores.begin(), servidores.end(), [nome_servidor_temp](Servidor servidor) {
            return servidor.getNome() == nome_servidor_temp;
        });

        // Captura e armazena a data e hora atual
        char dataHora[100];
        time_t s = time(nullptr);

        // Converte a data e hora para string
        strftime(dataHora, 50, "%d/%m/%Y - %R", localtime(&s));

        // Cria a mensagem a ser enviada
        Mensagem nova_mensagem(dataHora, usuarioLogadoId, mensagem);

        // Verifica se o envio foi realizada com sucesso
        it_servidor->enviaMensagem(nomeCanalConectado, nova_mensagem);

        return "Mensagem enviada!";
    }

    return "Não está conectado";
}

// Função do comando "list-messages"
std::string Sistema::list_messages(){
    return "list_messages NÃO IMPLEMENTADO";
}