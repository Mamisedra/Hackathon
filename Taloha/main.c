#include "game.h"

void sdl_loop(SDL_Parameters *sdlParams) {
	SDL_Event event;
	char inputText[256] = "";
	int textLength = 0;
	int running = 1;
	int submitClicked = 0;

	while (running) {
		sdl_handle_input(&event, inputText, &textLength, &running, &submitClicked, sdlParams);
		sdl_render(sdlParams, inputText);

		if (submitClicked) {
			char *text = inputText;
			int		reponse = 0;
			if (strcmp(text, "ondry") == 0)
			{
				printf("%s TSy azoko pr\n", text);
				reponse = 1;
				sound_play(sdlParams->sound[0]);
			}
			printf("Submitted Text: %s\n", inputText);
			if (reponse != 1)
			{
				sound_play(sdlParams->sound[1]);
				reponse = 0;
			}
			submitClicked = 0;
		}
	}
}

int main(int argc, char *argv[])
{
	SDL_Parameters sdlParams;

	if (sdl_init(&sdlParams) != 0) {
		return 1;
	}

	sdl_loop(&sdlParams);
	sdl_clean_up(&sdlParams);

	return 0;
}