#include "SewPatApp.h"
#include "SdlEngine.h"
#include "XlsxParser.h"
#include "SewPatternDrawer.h"
#include "DxfFileHandler.h"

#include <fstream>

SewPatApp::SewPatApp()
{
}

SewPatApp::~SewPatApp()
{
}

int SewPatApp::Run() const
{
	auto parser = XlsxParser();
	auto drawer = SewPatternDrawer();
	auto dxfFileHandler = DxfFileHandler();
	SdlEngine engine(parser, drawer, dxfFileHandler);

	try
	{
		engine.Init()
			.CreateMainWindow()
			  .InitImgSupport()
			  .CreateRenderer()
			  .StartLoop();
	}
	catch (const std::exception& ex)
	{
		std::ofstream logFile("error_log.txt", std::ios_base::out | std::ios_base::app); //TODO: Create Logger & Exception Handler*
		logFile << "Standard Exception thrown: " << ex.what() << '\n';
		return 1;
	}
	catch (...)
	{
		std::ofstream logFile("error_log.txt", std::ios_base::out | std::ios_base::app);
		logFile << "Unknown Exception thrown!" << '\n';
		return 1;
	}
	return 0;
}
