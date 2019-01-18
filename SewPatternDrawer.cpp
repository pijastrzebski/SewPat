#include "SewPatternDrawer.h"
#include "SDL.h"


void SewPatternDrawer::DrawLine(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	SDL_RenderClear(renderer);

	const auto POINTS_COUNT = 4;
	SDL_Point points[POINTS_COUNT] = {
		{320, 200},
		{300, 240},
		{340, 240},
		{320, 200}
	};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(renderer, points, POINTS_COUNT);
}
