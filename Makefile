.PHONY: clean

all: bin build main_client1 main_server1

main_client1: main_client1.o func.o
	gcc -g -pthread build/main_client1.o build/func.o -o bin/main_client1

main_server1: main_server1.o func.o
	gcc -g -pthread  build/main_server1.o build/func.o -o bin/main_server1

main_server1.o: src/first_scheme/main_server.c src/func.h
	gcc -g -pthread  -c src/first_scheme/main_server.c -o build/main_server1.o

main_client1.o: src/first_scheme/main_client.c src/func.h
	gcc -g -pthread  -c src/first_scheme/main_client.c -o build/main_client1.o

func.o: src/func.c src/func.h
	gcc -g -pthread  -c src/func.c -o build/func.o

bin:
	mkdir bin

build:
	mkdir build

clean:
	rm -rf bin build
