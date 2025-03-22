all:
	g++ -I src/include -L src/lib -o testProgram main.cpp game.cpp TextureManager.cpp FontManager.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf