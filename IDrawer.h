#pragma once

struct SDL_Renderer;

struct IDrawer
{
	virtual void DrawLine(SDL_Renderer *renderer) = 0;
};