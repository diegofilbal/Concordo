#include <algorithm>
#include <fstream>
#include <iostream>
#include <time.h>
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
    idCanalConectado = 0;
}

// Salva todos os dados do sistema
void Sistema::salvar() const{
    // Salva usuários e servidores
    salvarUsuarios();
    salvarServidores();
}

// Salva os dados dos usuários cadastrados 
void Sistema::salvarUsuarios() const{

    // Abre o arquivo a ser usado para armazenar os dados
    std::ofstream os_usuarios("database/usuarios.txt");

    // Verifica se a abertura foi bem sucedida
    if(os_usuarios) {

        // Imprime a quantidade de usuarios cadastrados
        os_usuarios << usuarios.size() << std::endl;

        // Imprime as credenciais de cada usuário do sistema
        for(auto it_usuario = usuarios.begin(); it_usuario != usuarios.end(); ++it_usuario) {
            os_usuarios << it_usuario->getId() << std::endl;
            os_usuarios << it_usuario->getNome() << std::endl;
            os_usuarios << it_usuario->getEmail() << std::endl;
            os_usuarios << it_usuario->getSenha() << std::endl;
        }

    }else
        std::cerr << "Erro ao salvar usuários! " << std::endl;
    
    os_usuarios.close();
}

// Salva os dados dos servidores cadastrados
void Sistema::salvarServidores() const{

    // Abre o arquivo a ser usado para armazenar os dados
    std::ofstream ofs_servidores("database/servidores.txt");

    // Verifica se a abertura foi bem sucedida
    if(ofs_servidores){

        // Imprime a quantidade de servidores cadastrados
        ofs_servidores << servidores.size() << std::endl;

        // Imprime os dados de cada servidor do sistema
        for(auto it_servidor = servidores.begin(); it_servidor != servidores.end(); ++it_servidor) {
            
            // Dados dos servidores
            ofs_servidores << it_servidor->getUsuarioDonoID() << std::endl;
            ofs_servidores << it_servidor->getNome() << std::endl;
            ofs_servidores << it_servidor->getDescricao() << std::endl;
            ofs_servidores << it_servidor->getCodigoConvite() << std::endl;

            // Dados dos membros dos servidores
            std::vector <int> partIDs = it_servidor->getParticipantesIDs();
            ofs_servidores << partIDs.size() << std::endl;
            for(auto it_p = partIDs.begin(); it_p != partIDs.end(); ++it_p)
                ofs_servidores << *it_p << std::endl;

            // Dados dos canais dos servidores
            std::vector <std::shared_ptr <Canal>> v_canais = it_servidor->getCanais();
            ofs_servidores << v_canais.size() << std::endl;
            for(auto it_c = v_canais.begin(); it_c != v_canais.end(); ++it_c) {
                ofs_servidores << (*it_c)->getID() << std::endl;
                ofs_servidores << (*it_c)->getNome() << std::endl;
                if(std::dynamic_pointer_cast <CanalTexto> (*it_c))
                    ofs_servidores << "TEXTO" << std::endl;
                if(std::dynamic_pointer_cast <CanalVoz> (*it_c))
                    ofs_servidores << "VOZ" << std::endl;

                // Dados das mensagens dos canais
                std::vector <Mensagem> me = (*it_c)->listaMensagens();
                ofs_servidores << me.size() << std::endl;
                for(auto it_m = me.begin(); it_m != me.end(); ++it_m) {
                    ofs_servidores << it_m->getEnviadaPor() << std::endl;
                    ofs_servidores << it_m->getDataHora() << std::endl;
                    ofs_servidores << it_m->getConteudo() << std::endl;
                }
            }
        }

    }else
        std::cerr << "Erro ao salvar servidores!" << std::endl;

    ofs_servidores.close();
}

// Restaura todos os dados previamente cadastrados
void Sistema::carregar(){
    // Restaura usuários e servidores
    carregarUsuarios();
    carregarServidores();
}

// Restaura os dados de usuários previamente cadastrados
void Sistema::carregarUsuarios(){

    // Abre o arquivo a ser usado para ler os dados
    std::ifstream ifs_usuarios("database/usuarios.txt");

    // Verifica se a abertura do arquivo foi bem sucedida
    if(ifs_usuarios){

        // Verifica se o arquivo não está vazio
        if(ifs_usuarios.peek() != std::ifstream::traits_type::eof()){

            // Apaga todos os usuários para evitar repetição no salvamento
            usuarios.clear();

            // Variável para armazenar conteúdo das linhas do documento
            std::string linha;

            // Variáveis para armazenar os dados dos usuários
            std::string qtd, id, nome, email, senha;

            // Lê a quantidade de usuários cadastrados
            getline(ifs_usuarios, qtd);

            // Faz a leitura dos dados de cada usuário
            for(int u = 0; u < stoi(qtd); ++u){
                getline(ifs_usuarios, id);
                getline(ifs_usuarios, nome);
                getline(ifs_usuarios, email);
                getline(ifs_usuarios, senha);

                // Cria e cadastra o novo usuário no sistema
                Usuario novo_usuario(stoi(id), email, senha, nome);
                usuarios.push_back(novo_usuario);
            }
        }
        
    }else
        std::cerr << "Nâo foi possível restaurar usuários!" << std::endl;
}

// Restaura os dados de servidores previamente cadastrados
void Sistema::carregarServidores(){

    // Abre o arquivo a ser usado para ler os dados
    std::ifstream ifs_servidores("database/servidores.txt");

    // Verifica se a abertura do arquivo foi bem sucedida
    if(ifs_servidores){

        // Verifica se o arquivo não está vazio
        if(ifs_servidores.peek() != std::ifstream::traits_type::eof()){

            // Apaga todos os servidores para evitar repetição no salvamento
            servidores.clear();

            // Variáveis para armazenar os dados dos servidores, canais e mensagens
            std::string s_qtd, s_donoID, s_nome, s_desc, s_cod, s_numPart, s_partID;
            std::string c_qtd, c_ID, c_nome, c_tipo;
            std::string m_qtd, m_remID, m_dataHora, m_con;

            // Lê a quantidade de usuários cadastrados
            getline(ifs_servidores, s_qtd);

            // Faz a leitura dos dados de cada servidor
            for(int s = 0; s < stoi(s_qtd); ++s) {
                getline(ifs_servidores, s_donoID);
                getline(ifs_servidores, s_nome);
                getline(ifs_servidores, s_desc);
                getline(ifs_servidores, s_cod);
                
                // Cria e cadastra o novo servidor no sistema
                Servidor novo_servidor(stoi(s_donoID), s_nome);
                novo_servidor.setDescricao(s_desc);
                novo_servidor.setCodigoConvite(s_cod);

                // Lê o número de participantes do servidor
                getline(ifs_servidores, s_numPart);

                // Faz a leitura do ID de todos os participantes e os adiciona ao servidor
                for(int p = 0; p < stoi(s_numPart); ++p){
                    getline(ifs_servidores, s_partID);
                    novo_servidor.adicionaParticipante(stoi(s_partID));
                }

                // Lê o número de canais do servidor
                getline(ifs_servidores, c_qtd);

                // Faz a leitura dos dados dos canais e insere no servidor
                for(int c = 0; c < stoi(c_qtd); ++c) {
                    getline(ifs_servidores, c_ID);
                    getline(ifs_servidores, c_nome);
                    getline(ifs_servidores, c_tipo);

                    // Cria ponteiro inteligente de canal
                    std::shared_ptr <Canal> novo_canal;

                    // Instancia o canal de acordo com seu tipo
                    if(c_tipo == "TEXTO")
                        novo_canal = std::make_shared <CanalTexto> (stoi(c_ID), c_nome);
                    else
                        novo_canal = std::make_shared <CanalVoz> (stoi(c_ID), c_nome);

                    // Lê a quantidade de mensagens do canal
                    getline(ifs_servidores, m_qtd);

                    // Faz a leitura dos dados das mensagens do canal
                    for(int m = 0; m < stoi(m_qtd); ++m) {
                        getline(ifs_servidores, m_remID);
                        getline(ifs_servidores, m_dataHora);
                        getline(ifs_servidores, m_con);

                        // Cria e adiciona a mensagem ao canal
                        Mensagem nova_mensagem(m_dataHora, stoi(m_remID), m_con);
                        novo_canal->enviaMensagem(nova_mensagem);
                    }

                    novo_servidor.criaCanal(novo_canal);
                }

                servidores.push_back(novo_servidor);
            }
        }

    } else
        std::cerr << "Nâo foi possível restaurar usuários!" << std::endl;
}

// Função do comando "quit"
std::string Sistema::quit(){

    // Restaura os dados de usuários e servidores
    carregar();

    return "Saindo do Concordo...";
}

// Função do comando "create-user"
std::string Sistema::create_user(const std::string email, const std::string senha, const std::string nome){
    
    // Restaura os dados de usuários e servidores
    carregar();

    // Verifica se o usuário inseriu todos os campos
    if(nome.empty())
        return "Informe todos os dados necessários do usuário!";

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

    // Salva os dados no arquivo
    salvar();

    return "Usuário criado!";
}

// Função do comando "login"
std::string Sistema::login(const std::string email, const std::string senha){

    // Restaura os dados de usuários e servidores
    carregar();
    
    // Procura algum usuário com o email e senha inseridos
    auto it_usuario = std::find_if(usuarios.begin(), usuarios.end(), [email, senha](Usuario usuario) {
        return usuario.getEmail() == email && usuario.getSenha() == senha;
    });

    // Verifica se a busca foi bem sucedida
    if(it_usuario != usuarios.end()){

        // Define qual usuário está logado no sistema
        usuarioLogadoId = it_usuario->getId();

        // Define que o usuário não está conectado a nenhum canal
        if(idCanalConectado) leave_channel();

        // Define que o usuário não está conectado a nenhum servidor
        if(!nomeServidorConectado.empty()) leave_server();

        return "Logado como " + it_usuario->getEmail() + "!";
    }

    return "Senha ou usuário inválidos!";
}

// Função do comando "disconnect"
std::string Sistema::disconnect(){

    // Restaura os dados de usuários e servidores
    carregar();

    // Verifica algum usuário está logado
    if(usuarioLogadoId){
        
        // Guarda o retorno da função em uma string
        std::string retorno = "Desconectando usuário " + usuarios[usuarioLogadoId - 1].getEmail();

        // Define que o usuário não está conectado a nenhum canal
        if(idCanalConectado) leave_channel();

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

    // Restaura os dados de usuários e servidores
    carregar();

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

        // Salva os dados no arquivo
        salvar();

        return "Servidor criado!";
    }

    return "Não está conectado!";
}

// Função do comando "set-server-desc"
std::string Sistema::set_server_desc(const std::string nome, const std::string descricao){

    // Restaura os dados de usuários e servidores
    carregar();

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

                // Salva os dados no arquivo
                salvar();

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

    // Restaura os dados de usuários e servidores
    carregar();

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

                // Salva os dados no arquivo
                salvar();

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

    // Restaura os dados de usuários e servidores
    carregar();

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

    // Restaura os dados de usuários e servidores
    carregar();
    
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

                // Salva os dados no arquivo
                salvar();

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

    // Restaura os dados de usuários e servidores
    carregar();

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
            if(idCanalConectado) leave_channel();

            // Salva os dados no arquivo
            salvar();

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

    // Restaura os dados de usuários e servidores
    carregar();

    // Verifica se há algum usuário logado
    if(usuarioLogadoId){

        // Verifica se o usuário já não está conectado a nenhum servidor no momento
        if(nomeServidorConectado.empty())
            return "Você não está visualizando nenhum servidor!";

        // Variável para guardar a string de retorno da função
        std::string retorno = "Saindo do servidor \'" + nomeServidorConectado + "\'!";

        // Desconecta o usuário do canal
        if(idCanalConectado) leave_channel();

        // Desconecta o usuário do servidor
        nomeServidorConectado = "";

        return retorno;
    }

    return "Não está conectado!";
}

// Função do comando "list-participants"
std::string Sistema::list_participants(){

    // Restaura os dados de usuários e servidores
    carregar();
    
    // Verifica se há algum usuário conectado
    if(usuarioLogadoId){

        // Verifica se o usuário não está conectado a nenhum servidor no momento
        if(nomeServidorConectado.empty())
            return "Não está conectado a nenhum servidor!";
        else{
            // Busca o servidor pelo nome
            std::string nomeServ = nomeServidorConectado;
            auto it_serv = std::find_if(servidores.begin(), servidores.end(), [nomeServ](Servidor servidor) {
                return servidor.getNome() == nomeServ;
            });

            // Verifica se nenhum servidor com esse nome existe 
            if(it_serv == servidores.end()){
                                
                // Desconecta o usuário do canal
                idCanalConectado = 0;

                // Desconecta o usuário do servidor
                nomeServidorConectado = "";

                return "Você não está visualizando nenhum servidor!";
            }
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

    // Restaura os dados de usuários e servidores
    carregar();

    // Verifica se há algum usuário conectado
    if(usuarioLogadoId) {

        // Verifica se o usuário está conectado a algum servidor
        if(nomeServidorConectado.empty())
            return "Não está conectado a nenhum servidor!";
        else{
            // Busca o servidor pelo nome
            std::string nomeServ = nomeServidorConectado;
            auto it_serv = std::find_if(servidores.begin(), servidores.end(), [nomeServ](Servidor servidor) {
                return servidor.getNome() == nomeServ;
            });

            // Verifica se nenhum servidor com esse nome existe 
            if(it_serv == servidores.end()){
                               
                // Desconecta o usuário do canal
                idCanalConectado = 0;

                // Desconecta o usuário do servidor
                nomeServidorConectado = "";

                return "Você não está visualizando nenhum servidor!";
            }
        }

        // Variável que armazena o nome do servidor conectado no momento
        std::string nome = nomeServidorConectado;

        // Busca o servidor que o usuário está conectado no momento
        auto it_servidor = std::find_if(servidores.begin(), servidores.end(), [nome](Servidor servidor) {
            return servidor.getNome() == nome;
        });

        // Recebe a lista de canais de texto do servidor atual
        std::vector <CanalTexto> c_texto = it_servidor->getCanaisTexto();

        // Recebe a lista de canais de voz do servidor atual
        std::vector <CanalVoz> c_voz = it_servidor->getCanaisVoz();

        // Verifica se não há nenhum canal cadastrado no servidor
        if(c_texto.empty() && c_voz.empty()){
            return "Nenhum canal no servidor!";
        }
        
        // Variável de retorno para concatenar o nome dos canais
        std::string retorno;

        // Verifica se há canais de texto cadastrados
        if(!c_texto.empty()){
            retorno += "#canais de texto\n";

            // Concatena o nome dos canais de texto à string de retorno
            for(auto it_canal = c_texto.begin(); it_canal != c_texto.end(); ++it_canal) {
                if(it_canal != c_texto.end() - 1)
                    retorno += it_canal->getNome() + "\n";
                else
                    retorno += it_canal->getNome();
            }
        }

        // Verifica se há canais de voz cadastrados
        if(!c_voz.empty()){

            if(!c_texto.empty()) retorno += "\n";

            retorno += "#canais de voz\n";

            // Concatena o nome dos canais de voz à string de retorno
            for(auto it_canal = c_voz.begin(); it_canal != c_voz.end(); ++it_canal){
                if(it_canal != c_voz.end() - 1)
                    retorno += it_canal->getNome() + "\n";
                else
                    retorno += it_canal->getNome();
            }
        }

        return retorno;
    }

    return "Não está conectado!";
}

// Função do comando "create-channel"
std::string Sistema::create_channel(const std::string nome, const std::string tipo){

    // Restaura os dados de usuários e servidores
    carregar();

    // Verifica se há algum usuário conectado
    if(usuarioLogadoId){

        // Verifica se o usuário está conectado a algum servidor
        if(nomeServidorConectado.empty())
            return "Não está conectado a nenhum servidor!";
        else{
            // Busca o servidor pelo nome
            std::string nomeServ = nomeServidorConectado;
            auto it_serv = std::find_if(servidores.begin(), servidores.end(), [nomeServ](Servidor servidor) {
                return servidor.getNome() == nomeServ;
            });

            // Verifica se nenhum servidor com esse nome existe 
            if(it_serv == servidores.end()){
                                
                // Desconecta o usuário do canal
                idCanalConectado = 0;

                // Desconecta o usuário do servidor
                nomeServidorConectado = "";

                return "Você não está visualizando nenhum servidor!";
            }
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
            std::vector <CanalTexto> c_texto = it_servidor->getCanaisTexto();

            // Busca um canal com o mesmo nome
            auto it_canal = std::find_if(c_texto.begin(), c_texto.end(), [nome](CanalTexto canal) {
                return canal.getNome() == nome;
            });

            // Verifica se a busca achou um canal com o mesmo nome
            if(it_canal != c_texto.end())
                return "Canal de texto \'" + nome + "\' já existe!";
            
            // Cria o canal de texto
            std::shared_ptr <Canal> novo_canal(new CanalTexto(it_servidor->qtdCanais() + 1, nome));

            // Verifica se a inserção foi realizada com sucesso
            if(it_servidor->criaCanal(novo_canal)){

                // Salva os dados no arquivo
                salvar();

                return "Canal de texto \'" + nome + "\' criado!";

            }else
                return "Erro inesperado ao criar canal de texto \'" + nome + "\'!";
        
        }else{

            // Recebe a lista de canais de voz do servidor atual
            std::vector <CanalVoz> c_voz = it_servidor->getCanaisVoz();

            // Busca um canal com o mesmo nome
            auto it_canal = std::find_if(c_voz.begin(), c_voz.end(), [nome](CanalVoz canal) {
                return canal.getNome() == nome;
            });

            // Verifica se a busca achou um canal com o mesmo nome
            if(it_canal != c_voz.end())
                return "Canal de voz \'" + nome + "\' já existe!";

            // Cria o canal de voz
            std::shared_ptr <Canal> novo_canal(new CanalVoz(it_servidor->qtdCanais() + 1, nome));

            // Verifica se a inserção foi realizada com sucesso
            if(it_servidor->criaCanal(novo_canal)){

                // Salva os dados no arquivo
                salvar();

                return "Canal de voz \'" + nome + "\' criado!";

            }else
                return "Erro inesperado ao criar canal de voz \'" + nome + "\'!";
        }
    }

    return "Não está conectado!";
}

// Função do comando "enter-channel"
std::string Sistema::enter_channel(const std::string nome, const std::string tipo){

    // Restaura os dados de usuários e servidores
    carregar();

    // Verifica se há algum usuário conectado
    if(usuarioLogadoId){

        // Verifica se o usuário está conectado a algum servidor
        if(nomeServidorConectado.empty())
            return "Não está conectado a nenhum servidor!";
        else{
            // Busca o servidor pelo nome
            std::string nomeServ = nomeServidorConectado;
            auto it_serv = std::find_if(servidores.begin(), servidores.end(), [nomeServ](Servidor servidor) {
                return servidor.getNome() == nomeServ;
            });

            // Verifica se nenhum servidor com esse nome existe 
            if(it_serv == servidores.end()){
                                
                // Desconecta o usuário do canal
                idCanalConectado = 0;

                // Desconecta o usuário do servidor
                nomeServidorConectado = "";

                return "Você não está visualizando nenhum servidor!";
            }
        }

        // Variável que armazena o nome do servidor conectado no momento
        std::string nome_servidor_temp = nomeServidorConectado;

        // Busca o servidor que o usuário está conectado no momento
        auto it_servidor = std::find_if(servidores.begin(), servidores.end(), [nome_servidor_temp](Servidor servidor) {
            return servidor.getNome() == nome_servidor_temp;
        });

        // Busca um canal de texto com o mesmo nome no servidor atual
        std::vector <CanalTexto> c_texto = it_servidor->getCanaisTexto();
        auto it_texto = std::find_if(c_texto.begin(), c_texto.end(), [nome](CanalTexto canal) {
            return canal.getNome() == nome;
        });

        // Busca um canal de voz com o mesmo nome no servidor atual
        std::vector <CanalVoz> c_voz = it_servidor->getCanaisVoz();
        auto it_voz = std::find_if(c_voz.begin(), c_voz.end(), [nome](CanalVoz canal) {
            return canal.getNome() == nome;
        });

        // Verifica se algum canal com o nome recebido foi encontrado
        if(it_texto == c_texto.end() && it_voz == c_voz.end())
            return "Canal \'" + nome + "\' não existe!";

        // Verifica se existem dois canais de tipos diferentes com o mesmo nome recebido
        if(it_texto != c_texto.end() && it_voz != c_voz.end()){

            // Verifica se o tipo informado é inválido
            if(tipo != "texto" && tipo != "voz")
                return "Dois canais de tipos diferentes com o nome \'" + nome + "\' encontrados!\nTente novamente informando um tipo válido!";

            // Conecta o usuário ao canal de texto
            if(tipo == "texto")
                idCanalConectado = it_texto->getID();

            // Conecta o usuário ao canal de voz
            if(tipo == "voz")
                idCanalConectado = it_voz->getID();

            return "Entrou no canal de " + tipo + " \'" + nome + "\'!";
        }

        // Conecta o usuário ao canal de texto
        if(it_texto != c_texto.end())
            idCanalConectado = it_texto->getID();

        // Conecta o usuário ao canal de voz
        if(it_voz != c_voz.end()) 
            idCanalConectado = it_voz->getID();

        return "Entrou no canal \'" + nome + "\'!";
    }

    return "Não está conectado!";
}

// Função do comando "leave-channel"
std::string Sistema::leave_channel(){

    // Restaura os dados de usuários e servidores
    carregar();
    
    // Verifica se há algum usuário logado
    if(usuarioLogadoId){

        // Verifica se o usuário está conectado a algum servidor
        if(nomeServidorConectado.empty())
            return "Não está conectado a nenhum servidor!";
        else{
            // Busca o servidor pelo nome
            std::string nomeServ = nomeServidorConectado;
            auto it_serv = std::find_if(servidores.begin(), servidores.end(), [nomeServ](Servidor servidor) {
                return servidor.getNome() == nomeServ;
            });

            // Verifica se nenhum servidor com esse nome existe 
            if(it_serv == servidores.end()){

                // Desconecta o usuário do canal
                idCanalConectado = 0;

                // Desconecta o usuário do servidor
                nomeServidorConectado = "";

                return "Você não está visualizando nenhum servidor!";
            }
        }

        // Verifica se o usuário já não está conectado a nenhum canal no momento
        if(!idCanalConectado)
            return "Você não está conectado a nenhum canal!";

        // Variável que armazena o nome do servidor conectado no momento
        std::string nome_servidor_temp = nomeServidorConectado;

        // Busca o servidor que o usuário está conectado no momento
        auto it_servidor = std::find_if(servidores.begin(), servidores.end(), [nome_servidor_temp](Servidor servidor) {
            return servidor.getNome() == nome_servidor_temp;
        });
    
        // Variável para guardar a string de retorno da função
        std::string retorno = "Saindo do canal \'" + it_servidor->getNomeCanal(idCanalConectado) + "\'!";

        // Desconecta o usuário do canal
        idCanalConectado = 0;

        return retorno;
    }

    return "Não está conectado!";
}

// Função do comando "send-message"
std::string Sistema::send_message(const std::string mensagem){

    // Restaura os dados de usuários e servidores
    carregar();

    // Verifica se há algum usuário conectado
    if(usuarioLogadoId){

        // Verifica se o usuário está conectado a algum servidor
        if(nomeServidorConectado.empty())
            return "Não está conectado a nenhum servidor!";
        else{
            // Busca o servidor pelo nome
            std::string nomeServ = nomeServidorConectado;
            auto it_serv = std::find_if(servidores.begin(), servidores.end(), [nomeServ](Servidor servidor) {
                return servidor.getNome() == nomeServ;
            });

            // Verifica se nenhum servidor com esse nome existe
            if(it_serv == servidores.end()){

                // Desconecta o usuário do canal
                idCanalConectado = 0;

                // Desconecta o usuário do servidor
                nomeServidorConectado = "";

                return "Você não está visualizando nenhum servidor!";
            }
        }

        // Verifica se o usuário está conectado a algum canal
        if(!idCanalConectado)
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

        // Envia a mensagem no canal
        it_servidor->enviaMensagem(idCanalConectado, nova_mensagem);

        // Salva os dados no arquivo
        salvar();

        return "Mensagem enviada!";
    }

    return "Não está conectado";
}

// Função do comando "list-messages"
std::string Sistema::list_messages(){

    // Restaura os dados de usuários e servidores
    carregar();

    if(usuarioLogadoId){

        // Verifica se o usuário está conectado a algum servidor
        if(nomeServidorConectado.empty())
            return "Não está conectado a nenhum servidor!";
        else{
            // Busca o servidor pelo nome
            std::string nomeServ = nomeServidorConectado;
            auto it_serv = std::find_if(servidores.begin(), servidores.end(), [nomeServ](Servidor servidor) {
                return servidor.getNome() == nomeServ;
            });

            // Verifica se nenhum servidor com esse nome existe 
            if(it_serv == servidores.end()){
                               
                // Desconecta o usuário do canal
                idCanalConectado = 0;

                // Desconecta o usuário do servidor
                nomeServidorConectado = "";

                return "Você não está visualizando nenhum servidor!";
            }
        }

        // Verifica se o usuário está conectado a algum canal
        if(!idCanalConectado)
            return "Não está conectado a nenhum canal!";

        // Busca o servidor que o usuário está conectado no momento
        std::string nome_servidor_temp = nomeServidorConectado;
        auto it_servidor = std::find_if(servidores.begin(), servidores.end(), [nome_servidor_temp](Servidor servidor) {
            return servidor.getNome() == nome_servidor_temp;
        });

        // Recebe o vector de retorno da função listaMensagens()
        std::vector <Mensagem> mensagens = it_servidor->listaMensagens(idCanalConectado);

        // Verifica se há mensagens a serem impressas
        if(mensagens.empty())
            return "Sem mensagens para exibir!";

        // String de retorno da função com as mensagens do canal
        std::string retorno;

        // Concatena as mensagens do canal à string de retorno
        for(auto it_msg = mensagens.begin(); it_msg != mensagens.end(); ++it_msg) {
            if(it_msg != mensagens.end() - 1)
                retorno += usuarios[it_msg->getEnviadaPor() - 1].getNome() + " <" + it_msg->getDataHora() + ">: " + it_msg->getConteudo() + "\n";
            else
                retorno += usuarios[it_msg->getEnviadaPor() - 1].getNome() + " <" + it_msg->getDataHora() + ">: " + it_msg->getConteudo();
        }

        return retorno;
    }

    return "Não está conectado!";
}