.PHONY: all clean

all: game.exe

clean:
	del game.exe

game.exe: game.o
	g++ game.o -o game.exe -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32
	del game.o

game.o:
	g++ -c game.cpp -DSFML_STATIC