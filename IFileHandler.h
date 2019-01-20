#pragma once

struct CalculatedResults;

struct IFileHandler
{
	virtual void WriteToFile(const CalculatedResults&) const = 0;
};
