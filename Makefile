# Compila todos os arquivos e gera o executável
all: create_dir concordo

# Cria pasta para armazenar os arquivos objetos
create_dir:
	mkdir -p bin

# Compila o arquivo node.cpp e gera o arquivo objeto sistema.o
bin/sistema.o: src/sistema.cpp
	g++ src/sistema.cpp -Iinclude -O0 -g -Wall -ansi -pedantic -std=c++11 -c -o bin/sistema.o

# Compila o arquivo node.cpp e gera o arquivo objeto executor.o
bin/executor.o: src/executor.cpp bin/sistema.o
	g++ src/executor.cpp -Iinclude -O0 -g -Wall -ansi -pedantic -std=c++11 -c -o bin/executor.o

# Compila o arquivo node.cpp e gera o arquivo objeto usuario.o
bin/usuario.o: src/usuario.cpp bin/executor.o
	g++ src/usuario.cpp -Iinclude -O0 -g -Wall -ansi -pedantic -std=c++11 -c -o bin/usuario.o

# Compila o arquivo node.cpp e gera o arquivo objeto concordo.o
bin/concordo.o: src/concordo.cpp bin/sistema.o bin/executor.o bin/usuario.o
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
