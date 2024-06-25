#include "game.h"
/*
int main(int argc, char* argv[]) {
    SDLApp app;

    if (!initSDL(&app, "Hello SDL2", 640, 480)) {
        return 1;
    }

    // Start accepting text input events
    SDL_StartTextInput();

    mainloop(&app);

    // Stop accepting text input events
    SDL_StopTextInput();

    cleanupSDL(&app);

    return 0;
}*/
Quiz quizzes[] = {
    {"Question 1", "answer1", "Hint for question 1"},
    {"Question 2", "answer2", "Hint for question 2"},
    // Add more questions as needed
};

const int quizzesCount = sizeof(quizzes) / sizeof(quizzes[0]);

int main(int argc, char* argv[]) {
    SDLApp app;

    if (!initSDL(&app, "Hello SDL2", 640, 480)) {
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
