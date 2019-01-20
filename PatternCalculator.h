#pragma once

#include "SSZ_ParserResults.h"
#include "CalculatedResults.h"

class PatternCalculator
{
public:
	PatternCalculator() = default;
	~PatternCalculator() = default;

	CalculatedResults Calculate(const SSZ_ParserResults& results);
};