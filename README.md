# **Concordo**

O _Concordo_ é um programa com recursos similares ao Discord (somente em modo texto e sem recursos de rede) implementado em C++!

## Instalando e executando

Com o terminal aberto no diretório em que deseja baixar o projeto, digite:

    $ git clone https://github.com/diegofilbal/Concordo.git

Entre no diretório do projeto com:

    $ cd Concordo

Para compilar e executar o programa, digite:

    $ make run

Ou para executar com as entradas fornecidas em [script_comandos.txt](script_comandos.txt), insira:

    $ make run_script

Também é possível apagar o arquivo executável e a pasta de arquivos objeto com o comando:

    $ make clean

## Como usar o sistema

A utilização do programa é feita a partir de comandos. A listagem dos comandos disponíveis e uma breve explicação de suas funcionalidades com exemplos está disposta abaixo.

> Observação: Apenas os comandos _create-user_, _login_ e _quit_ não exigem que haja algum usuário conectado para executá-los. As demais operações necessitam de um usuário conectado.

### Comando _quit_

Para fechar a aplicação, use o comando _quit_:

    quit
    "Saindo do Concordo..."

> Este comando pode ser executado a qualquer momento pelo usuário.

### Comando _create-user_

Para cadastrar um novo usuário ao sistema, digite o comando _create-user_ seguido do _email_, _senha_ e _nome_ do usuário, respectivamente:

    create-user diego@email.com senha123 Diego Filgueiras
    "Criando usuário Diego Filgueiras (diego@email.com)"
    "Usuário criado!"

O email do usuário deve ser único, caso haja a tentativa de cadastro de outro usuário com um email já utilizado, o programa informará o erro:

    create-user diego@email.com outrasenha Diego Maradona
    "Criando usuário Diego Maradona (diego@email.com)"
    "Usuário já existe!"

Todos os dados devem ser informados para a criação do usuário,. Caso isso não ocorra, o seguinte aviso será exibido:

    create-user diego@email.com senha123
    Informe todos os dados necessários do usuário!

### Comando _login_

Para conectar algum usuário ao sistema, insira o comando _login_ seguido do _email_ e _senha_ cadastrados anteriormente:

    login diego@email.com senha123
    "Logado como diego@email.com!"

Caso as informações de login do usuário sejam inseridas incorretamente, o programa informará o erro:

    login diego@email.com senhaerrada
    "Senha ou usuário inválidos!"

### Comando _disconnect_

Para desconectar o usuário conectado no momento, use o comando _disconnect_:

    disconnect
    "Desconectando usuário diego@email.com"

Caso não haja nenhum usuário conectado, a seguinte mensagem é exibida:

    disconnect
    "Não está conectado!"

### Comando _create-server_

Para criar um servidor, digite o comando _create-server_ seguido do _nome_ que deseja atribuir a ele:

    create-server among-us
    "Servidor criado!"

Caso o servidor já exista, o seguinte aviso será exibido:

    create-server among-us
    "Servidor com esse nome já existe!"

> O usuário que cria o servidor é inserido na lista de participantes automaticamente e é definido como o dono do servidor.

### Comando _set-server-desc_

Para definir ou atualizar a descrição de um servidor, insira o comando _set-server-desc_ seguido do _nome_ do servidor e da _descrição_ que deseja atribuir a ele:

    set-server-desc among-us Servidor para jogar Among Us em grupo
    "Descrição do servidor 'among-us' modificada!"

Caso o servidor não exista, a seguinte mensagem é exibida:

    set-server-desc cs-go Servidor para jogar CS:GO em grupo
    "Servidor 'cs-go' não existe!"

Se a mudança da descrição do servidor for solicitada por algum usuário que não o seu dono, o seguinte aviso é exibido:

    set-server-desc among-us Servidor para jogar Among Us em grupo
    "Você não pode alterar a descrição de um servidor que não foi criado por você!"

### Comando _set-server-invite-code_

Todos os servidores são criados sem código de convite (servidores abertos). Para definir ou atualizar o código de convite de um servidor para torná-lo fechado, use o comando _set-server-invite-code_ seguido do _nome_ do servidor e do _código de convite_ que deseja atribuir a ele:

    set-server-invite-code among-us codigo123
    "Código de convite do servidor 'among-us' modificado!"

Para remover o código de convite e torná-lo aberto novamente, digite o comando _set-server-invite-code_ seguido somente do _nome_ do servidor:

    set-server-invite-code among-us
    "Código de convite do servidor 'among-us' removido!"

Caso a mudança do código de convite de um servidor seja solicitada por algum usuário que não o seu dono, o seguinte aviso é exibido:

    set-server-invite-code among-us codigo000
    "Você não pode alterar o código de convite de um servidor que não foi criado por você!"

### Comando _list-servers_

Para listar todos os servidores do sistema, insira o comando _list-servers_:

    list-servers
    "among-us"
    "gartic"
    "minecraft"

### Comando _enter-server_

Para entrar em um servidor aberto, use o comando _enter-server_ seguido do _nome_ do servidor que deseja entrar:

    enter-server gartic
    "Entrou no servidor com sucesso!"

Se o servidor for fechado, digite o comando _enter-server_ seguido do _nome_ do servidor e do seu _código de convite_:

    enter-server among-us codigo123
    "Entrou no servidor com sucesso!"

Se o código de convite inserido estiver incorreto, a seguinte mensagem é exibida:

    enter-server among-us 123codigo
    "Código de convite inválido!"

Se o servidor for fechado e nenhum código de convite for inserido, o seguinte aviso é exibido:

    enter-server among-us
    "Servidor requer código de convite!"

> Além de adicionar o usuário à lista de participantes do servidor, sempre que o comando _enter-server_ é executado com sucesso, o sistema salva a informação de que o usuário está visualizando aquele servidor no momento.

### Comando _leave-server_

Para se desconectar do servidor que o usuário está visualizando no momento, insira o comando _leave-server_:

    leave-server
    "Saindo do servidor 'among-us'!"

Caso o usuário não esteja visualizando nenhum servidor no momento, a seguinte mensagem é exibida:

    leave-server
    "Você não está visualizando nenhum servidor!"

### Comando _list-participants_

Para listar o nome dos participantes do servidor que o usuário está visualizando no momento, digite o comando _list-participants_:

    list-participants
    "Diego Filgueiras"
    "Fulano da Silva"
    "Beltrano Oliveira"

### Comando _remove-server_

Para remover um servidor cadastrado, use o comando _remove-server_ seguido do _nome_ do servidor:

    remove-server gartic
    "Servidor 'gartic' removido!"

Se a remoção do servidor for solicitada por algum usuário que não o seu dono, o seguinte aviso é exibido:

    remove-server gartic
    "Você não é dono do servidor 'gartic'!"

> Caso o usuário estivesse conectado ao servidor removido, a desconexão é feita de forma automática. O mesmo ocorre caso o usário estivesse conectado a algum canal deste servidor.

### Comando _create-channel_

Para criar um canal no servidor ao qual o usuário está conectado no momento, insira o comando _create-channel_ seguido do _nome_ que deseja atribuir ao novo canal e do seu _tipo_ (texto ou voz):

    create-channel bate-papo-among texto
    "Canal de texto 'bate-papo-among' criado!"

Caso o usuário tente criar um canal com o mesmo nome e de mesmo tipo de algum outro canal já existente, a seguinte mensagem é exibida:

    create-channel bate-papo-among texto
    "Canal de texto 'bate-papo-among' já existe!"

Caso o tipo do canal informado seja diferente de "texto" ou "voz", a seguinte mensagem é exibida:

    create-channel impostores tipo-errado
    "Tipo de canal inválido!"

Se o usuário não estiver conectado a nenhum servidor, o seguinte aviso é exibido:

    create-channel airship voz
    "Não está conectado a nenhum servidor!"

### Comando _list-channels_

Para listar todos os canais de texto e de áudio do servidor ao qual o usuário está conectado no momento, digite o comando _list-channels_:

    list-channels
    "#canais de texto"
    "bate-papo-among"
    "#canais de voz"
    "bate-papo-among"
    "the-skeld"
    "mira-hq"
    "polus"

Se o servidor não tiver nenhum canal cadastrado, o seguinte aviso é exibido:

    list-channels
    "Nenhum canal no servidor!"

### Comando _enter-channel_

Para entrar em um canal de audio ou de texto do servidor ao qual o usuário está conectado no momento, use o comando _enter-channel_ seguido do _nome_ do canal que deseja entrar:

    enter-channel the-skeld
    "Entrou no canal 'the-skeld'!"

Caso não exista nenhum canal com o nome informado, a seguinte mensagem é exibida:

    enter-channel outro
    "Canal 'outro' não existe!"

Se existirem dois canais de tipos diferentes com o nome informado, o usuário também deverá especificar o _tipo_ do canal que deseja entrar:

    enter-channel bate-papo-among voz
    Entrou no canal de voz 'bate-papo-among'!

Caso o tipo informado seja inválido ou vazio, o seguinte aviso é exibido:

    enter-channel bate-papo-among
    "Dois canais de tipos diferentes com o nome 'bate-papo-among' encontrados!"
    "Tente novamente informando um tipo válido!"

### Comando _send-message_

Para mandar uma mensagem no canal ao qual o usuário está conectado no momento - seja ele de voz ou de texto - insira o comando _send-message_ seguido da _mensagem_ que deseja enviar:

    send-message tenho scan vem cmg
    "Mensagem enviada!"

Se a mensagem for vazia, a seguinte mensagem é exibida:

    send-message
    "Não é possível enviar uma mensagem vazia!"

Caso o usuário não esteja conectado a nenhum canal, o seguinte aviso é exibido:

    send-message o ciano me matooou
    "Não está conectado a nenhum canal!"

> Diferentemente dos canais de texto, nos canais de voz somente a última mensagem enviada é armazenada pelo sistema, conforme as especificações do trabalho.

### Comando _list-messages_

Para listar as mensagens do canal ao qual o usuário está conectado no momento, digite o comando _list-messages_:

    list-messages
    "Marrom <12/04/2021 - 17:49>: acho que o vermelho tava me seguindo"
    "Preto <12/04/2021 - 17:49>: ciano mt suspeito"
    "Ciano <12/04/2021 - 17:50>: eu pq????"
    "Laranja <12/04/2021 - 17:51>: eh o amarelo ctz"
    "Laranja <12/04/2021 - 17:51>: se n for pode me tirar na próxima"
    "Ciano <12/04/2021 - 17:52>: ok"

Se não houver mensagens cadastradas no canal, a seguinte mensagem é exibida:

    list-messages
    "Sem mensagens para exibir!"

Caso o usuário não esteja conectado a nenhum canal, o seguinte aviso é exibido:

    list-messages
    "Não está conectado a nenhum canal!"

## Limitações do sistema

- Devido à forma em que a identificação do canal conectado é feita, definida pelo documento de especificações do trabalho, em canais de mesmo nome e de tipos diferentes, é possível que o envio de mensagens não seja executado no canal correto, pois a operação é realizada no primeiro canal encontrado com o nome inserido pelo usuário.

## Dificuldades de implementação

- Afim de evitar vazamento de memória no armazenamento de canais da classe Servidor, foram utilizados ponteiros inteligentes, mais precisamente o `std::shared_ptr`, em vez de ponteiros comuns. Dessa forma, a função `std::dynamic_cast`, que estava sendo utilizada até então com os ponteiros comuns, aprensentou vários erros seguidos sem sucesso de solução. Por fim, o problema foi resolvido utilizando a função `std::dynamic_pointer_cast` para identificar o tipo de canal que o ponteiro faz referência.

## Autoria

Desenvolvido por [Diego Filgueiras Balderrama](https://github.com/diegofilbal) a partir do [código base](https://github.com/isaacfranco/lp1-concordo-base) do professor Isaac Franco Fernandes.
