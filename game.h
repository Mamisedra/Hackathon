#ifndef GAME_H
# define GAME_H

# define WIDTH 1920
# define HEIGHT 1080

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_render.h>

typedef struct s_app
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	int				win_width;
	int				win_height;
}				t_app;


int		initSDL(t_app *app, const char *title, int width, int height);
void	cleanupSDL(t_app *app);
int		main(int argc, char* argv[]);
void	mainLoop(t_app* app);
void	renderLeftRegion(SDL_Renderer* renderer, int width, int height);

void	renderRightRegion(SDL_Renderer* renderer, int width, int height);

#endif
