#ifndef GAME_H
# define GAME_H

# define WIDTH 1920
# define HEIGHT 1080

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_render.h>

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	TTF_Font *font;
	SDL_Rect textFieldRect;
	SDL_Rect submitButtonRect;
	Mix_Chunk *sound[2];
} SDL_Parameters;

// Function prototypes
int		sdl_init(SDL_Parameters *sdlParams);
void	sound_play(Mix_Chunk *music);
void	sdl_clean_up(SDL_Parameters *sdlParams);
void	sdl_handle_input(SDL_Event *event, char *inputText, int *textLength, int *running, int *submitClicked, SDL_Parameters *sdlParams);
void	sdl_render(SDL_Parameters *sdlParams, const char *inputText);
void	sdl_loop(SDL_Parameters *sdlParams);
void	sound_input(SDL_Parameters *sdlParams);

#endif
