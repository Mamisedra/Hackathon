#include "game.h"

int	main(int argc, char* argv[])
{
	t_app	app;
	int		running;

	if (!initSDL(&app, "Ko izy", WIDTH, HEIGHT))
		return (1);
	
	mainLoop(&app);
	cleanupSDL(&app);

	return (0);
}
