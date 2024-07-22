CC = gcc

CFLAGS = -Wall -std=c99 -g #Common flags

LIBS = -L./SDL2_ttf/.libs #Location of the library

LFLAGS = `sdl2-config --cflags --libs` -lSDL2_ttf #Library flags

INCLUDES = -I./SDL2_ttf #Location of the header files

SRCS = plateau.c fonctions_SDL.c Sprite.c evenement.c lecturefichier.c liste.c main.c menu.c monde.c fichier.c fin.c

OBJS = $(SRCS:.c=.o)

DEPS = fonctions_SDL.h Sprite.h evenement.h lecturefichier.h liste.h menu.h monde.h fichier.h fin.h

BIN = jeu

$(BIN) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN) $^ $(LIBS) $(LFLAGS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(LIBS) $(LFLAGS)

clean:
	$(RM) *.o *~ $(BIN)	
