#include "game.h"

void	renderLeftRegion(SDL_Renderer* renderer, int width, int height)
{
	SDL_Rect leftViewport = { 0, 0, width / 2, height };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &leftViewport);
}

void	renderRightRegion(SDL_Renderer* renderer, int width, int height)
{
	SDL_Rect rightViewport = { width / 2, 0, width / 2, height };
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rightViewport);
}

void	mainLoop(t_app* app)
{
    int	running;
	
	running = 1;
	SDL_Event event;

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = 0;
			else if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					running = 0;
			}
			else if (event.type == SDL_WINDOWEVENT)
			{
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					app->win_width = event.window.data1;
					app->win_height = event.window.data2;
					SDL_RenderSetLogicalSize(app->renderer,
							  app->win_width, app->win_height);
				}
			}
		}

		SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
		SDL_RenderClear(app->renderer);
		renderLeftRegion(app->renderer, app->win_width, app->win_height);
        renderRightRegion(app->renderer, app->win_width, app->win_height);
		SDL_RenderPresent(app->renderer);
	}
}

int initSDL(t_app *app, const char *title, int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
		return 0;
	}

	app->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED, width, height,
								SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (app->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 0;
	}

	app->renderer = SDL_CreateRenderer(app->window, -1,
									SDL_RENDERER_ACCELERATED
									| SDL_RENDERER_PRESENTVSYNC);
	if (app->renderer == NULL)
	{
		SDL_DestroyWindow(app->window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 0;
	}

	app->win_width = width;
	app->win_height = height;

	SDL_RenderSetLogicalSize(app->renderer, app->win_width, app->win_height);

	return (1);
}

void	cleanupSDL(t_app *app)
{
	if (app->renderer)
	{
		SDL_DestroyRenderer(app->renderer);
	}
	if (app->window)
	{
		SDL_DestroyWindow(app->window);
	}
	SDL_Quit();
}
