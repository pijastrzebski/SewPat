#pragma once

#include <string>
#include "IParserResults.h"

struct IParser
{
	virtual void Init() = 0;
	virtual bool Read(const std::string&) = 0;
	virtual bool Parse() = 0;
	virtual IParserResults* GetResults() = 0;
};
