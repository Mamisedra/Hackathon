#include "game.h"

void toLowerCase(char *str) {
    if (str == NULL) {
        return;
    }

    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

int initSDL(SDLApp* app, const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 0;
    }

    if (TTF_Init() == -1) {
        fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
        SDL_Quit();
        return 0;
    }

    app->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (app->window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 0;
    }

    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (app->renderer == NULL) {
        SDL_DestroyWindow(app->window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 0;
    }

    app->font = TTF_OpenFont("JetBrainsMonoNerdFont-Medium.ttf", 12);
    if (app->font == NULL) {
        SDL_DestroyRenderer(app->renderer);
        SDL_DestroyWindow(app->window);
        fprintf(stderr, "TTF_OpenFont Error: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        return 0;
    }

    app->width = width;
    app->height = height;

    return 1;
}

void cleanupSDL(SDLApp* app) {
    if (app->font) {
        TTF_CloseFont(app->font);
    }
    if (app->renderer) {
        SDL_DestroyRenderer(app->renderer);
    }
    if (app->window) {
        SDL_DestroyWindow(app->window);
    }
    TTF_Quit();
    SDL_Quit();
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        fprintf(stderr, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dst = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &dst);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

int showOptionsWindow(SDLApp* app, GameOption* options, int numOptions) {
    int running = 1;
    SDL_Event event;
    int selectedOption = -1;

    // Define window dimensions for the options window
    int optionsWidth = 400;
    int optionsHeight = 300;

    // Create a window for options
    SDL_Window* optionsWindow = SDL_CreateWindow("Options", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, optionsWidth, optionsHeight, SDL_WINDOW_SHOWN);
    if (optionsWindow == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Renderer* optionsRenderer = SDL_CreateRenderer(optionsWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (optionsRenderer == NULL) {
        SDL_DestroyWindow(optionsWindow);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return -1;
    }

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = 0;
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    for (int i = 0; i < numOptions; i++) {
                        if (options[i].selected) {
                            selectedOption = i;
                            running = 0;
                            break;
                        }
                    }
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                for (int i = 0; i < numOptions; i++) {
                    int boxX = 50;
                    int boxY = 50 + i * 40;
                    int boxSize = 30;

                    if (x >= boxX && x <= boxX + boxSize && y >= boxY && y <= boxY + boxSize) {
                        for (int j = 0; j < numOptions; j++) {
                            options[j].selected = 0;
                        }
                        options[i].selected = 1;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(optionsRenderer, 0, 0, 0, 255);
        SDL_RenderClear(optionsRenderer);

        for (int i = 0; i < numOptions; i++) {
            int boxX = 50;
            int boxY = 50 + i * 40;
            int boxSize = 30;

            if (options[i].selected) {
                SDL_SetRenderDrawColor(optionsRenderer, 0, 255, 0, 255);
            } else {
                SDL_SetRenderDrawColor(optionsRenderer, 255, 255, 255, 255);
            }

            SDL_Rect checkbox = { boxX, boxY, boxSize, boxSize };
            SDL_RenderFillRect(optionsRenderer, &checkbox);

            SDL_Color textColor = { 255, 255, 255, 255 };
            renderText(optionsRenderer, app->font, options[i].description, boxX + boxSize + 10, boxY + 5);
        }

        SDL_RenderPresent(optionsRenderer);
    }

    SDL_DestroyRenderer(optionsRenderer);
    SDL_DestroyWindow(optionsWindow);

    return selectedOption;
}

void resetGame(SDL_Color* leftColor, char* inputText, int* textLength, int* enterPressed, int* showRetryMessage, int* hintsShown, int* score) {
    leftColor->r = 255;
    leftColor->g = 255;
    leftColor->b = 255;
    inputText[0] = '\0';
    *textLength = 0;
    *enterPressed = 1;
    *showRetryMessage = 0;
    *hintsShown = 1;
    *score = 100;
}

void mainloop(SDLApp *app) {
    int running = 1;
    SDL_Event event;
    char inputText[256] = "";
    int textLength = 0;
    int enterPressed = 1; // Indicateur pour la validation par Entrée
    SDL_Color leftColor = {255, 255, 255, 255}; // Couleur de départ de la partie gauche
    char inputLower[256];
    int showRetryMessage = 0; // Indicateur pour afficher le message "Veuillez réessayer"
    int hintsShown = 1; // Variable pour suivre le nombre d'indices affichés (commence à 1)
    int score = 100; // Initialiser le score à 100
    int totalScore = 0; // Cumul des scores
    int gameStage = 1; // Étape du jeu (commence à 1)

    Uint32 colorChangeTime = 0;  // Temps du dernier changement de couleur
    Uint32 colorDuration = 500;  // Durée pendant laquelle la couleur change (en millisecondes)

    // Indices
    const char* hints[] = {
        "Toro voalohany: Izy dia biby",
        "Toro faharoa: Biby manana rambo lava",
        "Toro fahatelo: Sady miaina ao anaty rano no ety ambonin'ny tany",
        "Toro fahaefatra: mihinan-kena"
    };
    int numHints = sizeof(hints) / sizeof(hints[0]);

    while (running) {
        Uint32 currentTime = SDL_GetTicks(); // Obtenez le temps actuel en millisecondes

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = 0;
                } else if (event.key.keysym.sym == SDLK_BACKSPACE && textLength > 0) {
                    inputText[--textLength] = '\0';
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    if (strlen(inputText) > 0 && enterPressed) {
                        // Validation par Entrée
                        strcpy(inputLower, inputText);
                        toLowerCase(inputLower);

                        if (strcmp(inputLower, "voay") == 0) {
                            // Action pour bonne réponse
                            leftColor.r = 0;
                            leftColor.g = 255;
                            leftColor.b = 0;
                            enterPressed = 0; // Désactiver la validation par Entrée jusqu'à la prochaine bonne réponse
                            showRetryMessage = 0; // Réinitialiser le message "Veuillez réessayer"

                            // Cumuler le score final
                            totalScore += score;

                            // Réinitialiser la couleur après 500 millisecondes
                            SDL_Delay(500);
                            leftColor.r = 255;
                            leftColor.g = 255;
                            leftColor.b = 255;

                            // Passer à l'étape suivante du jeu
                            if (gameStage < 5) {
                                gameStage++;
                                resetGame(&leftColor, inputText, &textLength, &enterPressed, &showRetryMessage, &hintsShown, &score);
                            } else {
                                // Afficher le score final
                                char finalScoreText[100];
                                snprintf(finalScoreText, sizeof(finalScoreText), "Score final: %d", totalScore);
                                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Fin du jeu", finalScoreText, app->window);
                                running = 0;
                            }
                        } else {
                            // Action pour mauvaise réponse
                            leftColor.r = 255;
                            leftColor.g = 0;
                            leftColor.b = 0;
                            showRetryMessage = 1; // Afficher le message "Veuillez réessayer"

                            if (hintsShown < numHints) {
                                hintsShown++; // Augmenter le nombre d'indices affichés
                                score -= 25; // Décrémenter le score de 25
                            }

                            // Réinitialiser la couleur après 500 millisecondes
                            colorChangeTime = currentTime;
                        }

                        textLength = 0; // Réinitialiser l'inputText après validation
                        inputText[0] = '\0'; // Réinitialiser la chaîne de texte
                    }
                }
            } else if (event.type == SDL_TEXTINPUT) {
                if (textLength < sizeof(inputText) - 1) {
                    strcat(inputText, event.text.text);
                    textLength += strlen(event.text.text);
                }
            } else if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    app->width = event.window.data1;
                    app->height = event.window.data2;
                    SDL_RenderSetLogicalSize(app->renderer, app->width, app->height);
                }
            }
        }

        // Vérifiez si la couleur doit être réinitialisée
        if (currentTime - colorChangeTime >= colorDuration && (leftColor.r != 255 || leftColor.g != 255 || leftColor.b != 255)) {
            leftColor.r = 255;
            leftColor.g = 255;
            leftColor.b = 255;
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
        SDL_RenderClear(app->renderer);

        // Draw the left half
        SDL_Rect leftRect = {0, 0, app->width / 2, app->height};
        SDL_SetRenderDrawColor(app->renderer, leftColor.r, leftColor.g, leftColor.b, 255);
        SDL_RenderFillRect(app->renderer, &leftRect);

        // Draw the right half
        SDL_Rect rightRect = {app->width / 2, 0, app->width / 2, app->height};
        SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(app->renderer, &rightRect);

        // Render the hints on the right side, at the top left corner
        if (app->font) {
            int hintY = 10; // Starting Y position for hints
            for (int i = 0; i < hintsShown; i++) {
                int textWidth, textHeight;
                TTF_SizeText(app->font, hints[i], &textWidth, &textHeight);
                renderText(app->renderer, app->font, hints[i], app->width / 2 + 10, hintY);
                hintY += textHeight + 5; // Move down for the next hint
            }
        }

        // Render the score at the top right corner
        char scoreText[50];
        snprintf(scoreText, sizeof(scoreText), "Isa: %d", score);
        if (app->font) {
            int textWidth, textHeight;
            TTF_SizeText(app->font, scoreText, &textWidth, &textHeight);
            renderText(app->renderer, app->font, scoreText, app->width - textWidth - 10, 10);
        }

        // Render the input text on the right side, at the bottom
        if (app->font) {
            int textWidth, textHeight;
            TTF_SizeText(app->font, inputText, &textWidth, &textHeight);
            renderText(app->renderer, app->font, inputText, app->width - textWidth - 10, app->height - textHeight - 10);
        }

        // Render "Veuillez réessayer" message if showRetryMessage is true
        if (showRetryMessage) {
            const char *retryText = "Andramo indray azafady XD";
            SDL_Color messageColor = {255, 0, 0, 255}; // Couleur rouge pour le message
            int textWidth, textHeight;
            TTF_SizeText(app->font, retryText, &textWidth, &textHeight);
            renderText(app->renderer, app->font, retryText, app->width / 2 + 10, app->height - textHeight - 10);
        }

        // Present the renderer
        SDL_RenderPresent(app->renderer);
    }
}

