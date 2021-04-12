#include <string>
#include <vector>

#include "../include/canal.hpp"
#include "../include/canal_voz.hpp"

// Construtor
CanalVoz::CanalVoz() {
    // Inicializa o conteúdo da mensagem
    ultimaMensagem.setConteudo("");
}

// Construtor sobrecarregado
CanalVoz::CanalVoz(std::string const nome) : Canal(nome) {

}

// Envia uma mensagem no canal de voz
void CanalVoz::enviaMensagem(const Mensagem mensagem) {

    // Atualiza a última mensagem do canal
    ultimaMensagem.setDataHora(mensagem.getDataHora());
    ultimaMensagem.setEnviadaPor(mensagem.getEnviadaPor());
    ultimaMensagem.setConteudo(mensagem.getConteudo());
}

// Retorna um vector de um único elemento contendo a ultima mensagem enviada no canal 
std::vector <Mensagem> CanalVoz::listaMensagens() const{

    // Cria um vector de mensagens
    std::vector <Mensagem> retorno;

    // Insere a última mensagem no vector se a mensagem for válida
    if(!ultimaMensagem.getConteudo().empty()) retorno.push_back(ultimaMensagem);

    return retorno;
}