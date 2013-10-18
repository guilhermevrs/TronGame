all: generate
	./bin/TronGame
generate: matrixcontroller.o
	gcc -o bin/TronGame src/trongame.c bin/matrixcontroller.o -lGL -lGLU -lglut -W
matrixcontroller.o:
	gcc -o bin/matrixcontroller.o -c src/matrixcontroller.c -W
clean:
	rm -rf bin/*.o bin/TronGame