#pragma once

#include "IDrawer.h"

#include <vector>

class SewPatternDrawer : public IDrawer
{
public:
	SewPatternDrawer() = default;

	void DrawLine(SDL_Renderer *renderer) override;
};

