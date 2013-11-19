all: generate
	./bin/TronGame

generate: matrixcontroller.o rendercontroller.o texturehelper.o meshloader.o
	gcc -o bin/TronGame src/trongame.c bin/matrixcontroller.o bin/rendercontroller.o bin/texturehelper.o bin/meshloader.o  -lGL -lGLU -lglut -W

matrixcontroller.o:
	gcc -o bin/matrixcontroller.o -c src/matrixcontroller.c -W

rendercontroller.o:
	gcc -o bin/rendercontroller.o -c src/rendercontroller.c -W

texturehelper.o:
	gcc -o bin/texturehelper.o -c src/texturehelper.c -W

meshloader.o:
	gcc -o bin/meshloader.o -c src/meshloader.c -W

clean:
	rm -rf bin/*.o bin/TronGame