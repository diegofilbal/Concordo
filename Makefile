# Compila todos os arquivos e gera o executável
all: create_dir concordo

# Cria pasta para armazenar os arquivos objetos
create_dir:
	mkdir -p bin

# Compila o arquivo usuario.cpp e gera o arquivo objeto usuario.o
bin/usuario.o: src/usuario.cpp
	g++ src/usuario.cpp -Iinclude -O0 -g -Wall -ansi -pedantic -std=c++11 -c -o bin/usuario.o

# Compila o arquivo mensagem.cpp e gera o arquivo objeto mensagem.o
bin/mensagem.o: src/mensagem.cpp
	g++ src/mensagem.cpp -Iinclude -O0 -g -Wall -ansi -pedantic -std=c++11 -c -o bin/mensagem.o

# Compila o arquivo canal.cpp e gera o arquivo objeto canal.o
bin/canal.o: src/canal.cpp
	g++ src/canal.cpp -Iinclude -O0 -g -Wall -ansi -pedantic -std=c++11 -c -o bin/canal.o

# Compila o arquivo servidor.cpp e gera o arquivo objeto servidor.o
bin/servidor.o: src/servidor.cpp bin/mensagem.o bin/canal.o include/canal_texto.hpp include/canal_voz.hpp
	g++ src/servidor.cpp -Iinclude -O0 -g -Wall -ansi -pedantic -std=c++11 -c -o bin/servidor.o

# Compila o arquivo sistema.cpp e gera o arquivo objeto sistema.o
bin/sistema.o: src/sistema.cpp bin/usuario.o bin/servidor.o
	g++ src/sistema.cpp -Iinclude -O0 -g -Wall -ansi -pedantic -std=c++11 -c -o bin/sistema.o

# Compila o arquivo executor.cpp e gera o arquivo objeto executor.o
bin/executor.o: src/executor.cpp bin/sistema.o
	g++ src/executor.cpp -Iinclude -O0 -g -Wall -ansi -pedantic -std=c++11 -c -o bin/executor.o

# Compila o arquivo concordo.cpp e gera o arquivo objeto concordo.o
bin/concordo.o: src/concordo.cpp bin/executor.o bin/sistema.o
	g++ src/concordo.cpp -Iinclude -O0 -g -Wall -ansi -pedantic -std=c++11 -c -o bin/concordo.o

# Cria o arquivo executável
concordo: bin/concordo.o
	g++ bin/*.o -Iinclude -O0 -g -Wall -ansi -pedantic -std=c++11 -o concordo

# Executa o programa
run: all
	./concordo

run_script: all
	./concordo < script_comandos.txt

# Apaga a pasta de arquivos objetos e o executável
clean:
	rm -rf bin concordo
