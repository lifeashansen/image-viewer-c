all: run

build: main.c
	gcc -Wall -Wextra -lSDL3 -o image-viewer main.c

run: build
	./image-viewer samples/surprise.ppm
