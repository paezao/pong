SRC=src/*.c
BIN=game

all:
	mkdir -p bin
	gcc $(SRC) -L ../raylib/release/osx -I ../raylib/src -lglfw3 -lraylib -framework OpenGL -framework OpenAL -o bin/${BIN}

run: all
	./bin/${BIN}

clean:
	rm -rf bin
