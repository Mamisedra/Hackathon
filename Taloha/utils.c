#include "game.h"

void	sound_input(SDL_Parameters *sdlParams)
{
	sdlParams->sound[0] = Mix_LoadWAV("sound/vrai.wav");
	sdlParams->sound[1] = Mix_LoadWAV("sound/faux.wav");	
}
void	sound_play(Mix_Chunk *music)
{
	Mix_PlayChannel(-1, music, 0);
}

int sdl_init(SDL_Parameters *sdlParams) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return 1;
	}

	if (TTF_Init() != 0) {
		printf("Error initializing TTF: %s\n", TTF_GetError());
		SDL_Quit();
		return 1;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("Error initializing SDL_mixer: %s\n", Mix_GetError());
		TTF_Quit();
		SDL_Quit();
		return 1;
	}

	sdlParams->window = SDL_CreateWindow("My SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (sdlParams->window == NULL) {
		printf("Error creating window: %s\n", SDL_GetError());
		Mix_CloseAudio();
		TTF_Quit();
		SDL_Quit();
		return 1;
	}

	sdlParams->renderer = SDL_CreateRenderer(sdlParams->window, -1, SDL_RENDERER_ACCELERATED);
	if (sdlParams->renderer == NULL) {
		printf("Error creating renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(sdlParams->window);
		Mix_CloseAudio();
		TTF_Quit();
		SDL_Quit();
		return 1;
	}

	sdlParams->font = TTF_OpenFont("arial.ttf", 24);
	if (sdlParams->font == NULL) {
		printf("Error loading font: %s\n", TTF_GetError());
		SDL_DestroyRenderer(sdlParams->renderer);
		SDL_DestroyWindow(sdlParams->window);
		Mix_CloseAudio();
		SDL_Quit();
		TTF_Quit();
		return 1;
	}
	//taille et position
	sdlParams->textFieldRect = (SDL_Rect){ 1600, 1060, 300, 20 };
	sdlParams->submitButtonRect = (SDL_Rect){ 520, 100, 100, 50 };
	sound_input(sdlParams);
	SDL_StartTextInput();

	return 0;
}

void sdl_clean_up(SDL_Parameters *sdlParams) {
	SDL_StopTextInput();
	TTF_CloseFont(sdlParams->font);
	SDL_DestroyRenderer(sdlParams->renderer);
	SDL_DestroyWindow(sdlParams->window);
	Mix_FreeChunk(sdlParams->sound[0]);
	Mix_FreeChunk(sdlParams->sound[1]);
	Mix_CloseAudio();
	SDL_Quit();
	TTF_Quit();
}
