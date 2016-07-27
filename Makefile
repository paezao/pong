SRC=src/*.c
BIN=game

all:
	gcc $(SRC) -L ../raylib/release/osx -I ../raylib/src -lglfw3 -lraylib -framework OpenGL -o bin/${BIN}

run: all
	./bin/${BIN}
