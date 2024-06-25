#include "game.h"

int main(int argc, char* argv[]) {
    SDLApp app;

    if (!initSDL(&app, "Ko izy", WIDTH, HEIGHT)) {
        return 1;
    }

    mainloop(&app);

    cleanupSDL(&app);

    return 0;
}
