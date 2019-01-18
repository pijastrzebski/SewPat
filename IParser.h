#pragma once

#include <string>

struct IParser
{
	virtual void Init() = 0;
	virtual bool Read(const std::string&) = 0;
	virtual bool Parse() = 0;
};
