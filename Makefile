all:
	g++ -I sdl_src/include -L sdl_src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2