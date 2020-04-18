.PHONY: clean

all: bin build main_client1 main_server1 main_server2

main_client1: main_client1.o func_client.o func.o
	gcc -g -pthread build/main_client1.o build/func_client.o build/func.o -o bin/client1

main_server1: main_server1.o func_serv.o func.o
	gcc -g -pthread build/main_server1.o build/func_serv.o build/func.o -o bin/server1

main_server2: main_server2.o func_serv.o func.o
	gcc -g -pthread build/main_server2.o build/func_serv.o build/func.o -o bin/server2

main_server2.o: src/second_server.c src/func_serv.h
	gcc -g -pthread -c src/second_server.c -o build/main_server2.o

main_server1.o: src/first_server.c src/func.h
	gcc -g -pthread -c src/first_server.c -o build/main_server1.o

main_client1.o: src/main_client.c src/func_client.h
	gcc -g -pthread -c src/main_client.c -o build/main_client1.o

func_serv.o: src/func_serv.c src/func_serv.h
	gcc -g -pthread -c src/func_serv.c -o build/func_serv.o

func_client.o: src/func_client.c src/func_client.h
	gcc -g -pthread -c src/func_client.c -o build/func_client.o

func.o: src/func.c src/func.h
	gcc -g -pthread -c src/func.c -o build/func.o

bin:
	mkdir bin

build:
	mkdir build

clean:
	rm -rf bin build
