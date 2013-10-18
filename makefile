all: generate
	./TronGame
generate:
	gcc -o TronGame trongame.c -lGL -lGLU -lglut -W
clean:
	rm -rf *.o TronGame