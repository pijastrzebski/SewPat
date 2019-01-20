#include "DxfFileHandler.h"
#include "xdxfgen.h"


DxfFileHandler::DxfFileHandler()
{
}


DxfFileHandler::~DxfFileHandler()
{
}

void DxfFileHandler::WriteToFile(const CalculatedResults& results) const
{
	try
	{
		// write
		XDxfGen dxfGen;
		std::string fileName = "test.dxf";
		dxfGen.begin(fileName);

		dxfGen.line(35, 75, 200 - 35, 75);

		if (!dxfGen.end())
		{
			std::clog << "DxfFileHandler::WriteToFile: Error\n";
		}
		else
		{
			std::clog << "DxfFileHandler::WriteToFile: Success\n";
		}
	}
	catch (const std::exception& ex)
	{
		std::clog << "DxfFileHandler::WriteToFile Exception: " << ex.what() << '\n';
	}
	catch (...)
	{
		std::clog << "DxfFileHandler::WriteToFile Unknown Exception\n";
	}	
}
