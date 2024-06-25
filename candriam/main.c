#include "game.h"
/*
int main(int argc, char* argv[]) {
    SDLApp app;

    if (!initSDL(&app, "Ko izy", WIDTH, HEIGHT)) {
        return 1;
    }

    mainloop(&app);

    cleanupSDL(&app);

    return 0;
}*/ 

int main(int argc, char* argv[]) {
    SDLApp app;

    if (!initSDL(&app, "Ko izy", WIDTH, HEIGHT)) {
        return 1;
    }

    // Define game options
    GameOption options[] = {
        { "Biby andemika", 0 },
        { "Toerana malaza", 0 },
        { "Olona malaza", 0 }
    };
    int numOptions = sizeof(options) / sizeof(options[0]);

    int selectedOption = showOptionsWindow(&app, options, numOptions);
    if (selectedOption == -1) {
        cleanupSDL(&app);
        return 1;
    }

    // Start accepting text input events
    SDL_StartTextInput();

    mainloop(&app);

    // Stop accepting text input events
    SDL_StopTextInput();

    cleanupSDL(&app);

    return 0;
}
