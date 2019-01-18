#pragma once

struct IFileHandler
{
	virtual void WriteToFile() const = 0;
};
