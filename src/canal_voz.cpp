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
