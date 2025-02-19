all:
	g++ -I src/include -L src/lib -o testProgram game.cpp TextureManager.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image