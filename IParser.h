#pragma once

#include <string>

struct IParser
{
	virtual void Read(const std::string&) = 0;
};
