#include "game.h"

void sdl_handle_input(SDL_Event *event, char *inputText, int *textLength, int *running, int *submitClicked, SDL_Parameters *sdlParams) {
	while (SDL_PollEvent(event)) {
		switch (event->type) {
			case SDL_QUIT:
				*running = 0;
				break;
			case SDL_TEXTINPUT:
				if (*textLength + strlen(event->text.text) < 256) {
					strcat(inputText, event->text.text);
					*textLength += strlen(event->text.text);
				}
				break;
			case SDL_KEYDOWN:
				if (event->key.keysym.sym == SDLK_BACKSPACE && *textLength > 0) {
					inputText[--(*textLength)] = '\0';
				}
				if (event->key.keysym.sym == SDLK_RETURN) {
					*submitClicked = 1;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event->button.button == SDL_BUTTON_LEFT) {
					int x = event->button.x;
					int y = event->button.y;
					if (x >= sdlParams->submitButtonRect.x && x <= sdlParams->submitButtonRect.x + sdlParams->submitButtonRect.w &&
						y >= sdlParams->submitButtonRect.y && y <= sdlParams->submitButtonRect.y + sdlParams->submitButtonRect.h) {
						*submitClicked = 1;
					}
				}
				break;
		}
	}
}


void sdl_render(SDL_Parameters *sdlParams, const char *inputText) {
	SDL_SetRenderDrawColor(sdlParams->renderer, 63, 223, 169, 255); // Blue background
	SDL_RenderClear(sdlParams->renderer);

	SDL_Color textFieldColor = { 230, 230, 230 };
	SDL_SetRenderDrawColor(sdlParams->renderer, textFieldColor.r, textFieldColor.g, textFieldColor.b, 255);
	SDL_RenderFillRect(sdlParams->renderer, &sdlParams->textFieldRect);

	SDL_Color submitButtonColor = { 255, 255, 255 };
	SDL_SetRenderDrawColor(sdlParams->renderer, submitButtonColor.r, submitButtonColor.g, submitButtonColor.b, 255);
	SDL_RenderFillRect(sdlParams->renderer, &sdlParams->submitButtonRect);

	SDL_Surface *textSurface = TTF_RenderText_Solid(sdlParams->font, inputText, (SDL_Color){ 0, 0, 0 }); // Render text in black
	if (textSurface != NULL) {
		SDL_Texture *textTexture = SDL_CreateTextureFromSurface(sdlParams->renderer, textSurface);
		SDL_Rect textRect = { sdlParams->textFieldRect.x + 5, sdlParams->textFieldRect.y + 5, textSurface->w, textSurface->h };
		SDL_RenderCopy(sdlParams->renderer, textTexture, NULL, &textRect);
		SDL_DestroyTexture(textTexture);
		SDL_FreeSurface(textSurface);
	}

	// Render the "Submit" button text
	textSurface = TTF_RenderText_Solid(sdlParams->font, "Submit", (SDL_Color){ 0, 0, 0 });
	if (textSurface != NULL) {
		SDL_Texture *textTexture = SDL_CreateTextureFromSurface(sdlParams->renderer, textSurface);
		SDL_Rect textRect = { sdlParams->submitButtonRect.x + 10, sdlParams->submitButtonRect.y + 10, textSurface->w, textSurface->h };
		SDL_RenderCopy(sdlParams->renderer, textTexture, NULL, &textRect);
		SDL_DestroyTexture(textTexture);
		SDL_FreeSurface(textSurface);
	}

	SDL_RenderPresent(sdlParams->renderer);
}

