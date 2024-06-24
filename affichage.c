#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string.h>

// Structure to hold SDL parameters
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Rect textFieldRect;
    SDL_Rect submitButtonRect;
    Mix_Chunk *sound;
} SDL_Parameters;

// Function prototypes
int sdl_init(SDL_Parameters *sdlParams);
void sdl_clean_up(SDL_Parameters *sdlParams);
void sdl_handle_input(SDL_Event *event, char *inputText, int *textLength, int *running, int *submitClicked, SDL_Parameters *sdlParams);
void sdl_render(SDL_Parameters *sdlParams, const char *inputText);
void sdl_loop(SDL_Parameters *sdlParams);

int main() {
    SDL_Parameters sdlParams;
    if (sdl_init(&sdlParams) != 0) {
        return 1;
    }

    sdl_loop(&sdlParams);

    sdl_clean_up(&sdlParams);

    return 0;
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

    sdlParams->window = SDL_CreateWindow("My SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
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

    sdlParams->textFieldRect = (SDL_Rect){ 100, 100, 400, 50 };
    sdlParams->submitButtonRect = (SDL_Rect){ 520, 100, 100, 50 };

    SDL_StartTextInput();

    return 0;
}

void sdl_clean_up(SDL_Parameters *sdlParams) {
    SDL_StopTextInput();
    TTF_CloseFont(sdlParams->font);
    SDL_DestroyRenderer(sdlParams->renderer);
    SDL_DestroyWindow(sdlParams->window);
    Mix_CloseAudio();
    SDL_Quit();
    TTF_Quit();
}

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
    SDL_SetRenderDrawColor(sdlParams->renderer, 0, 0, 255, 255); // Blue background
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
			if (strcmp(text, "ondry") == 0)
			{
				printf("%s dia valiny marina\n", text);
				sdl_clean_up(sdlParams);
				exit(0);
			}
            printf("Submitted Text: %s\n", inputText);
            submitClicked = 0; // Reset the submit flag
        }
    }
}
