#pragma once

#include "IFileHandler.h"

class DxfFileHandler : public IFileHandler
{
public:
	DxfFileHandler();
	~DxfFileHandler();

	void WriteToFile(const CalculatedResults&) const override;
};

