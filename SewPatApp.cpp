#include "SewPatApp.h"
#include "SdlEngine.h"
#include "XlsxParser.h"
#include "SewPatternDrawer.h"
#include "DxfFileHandler.h"
#include "EventHandler.h"

#include <fstream>

SewPatApp::SewPatApp()
{
}

SewPatApp::~SewPatApp()
{
}

int SewPatApp::Run() const
{
	SdlEngine engine(std::make_unique<XlsxParser>(),
					 std::make_unique<SewPatternDrawer>(),
					 std::make_unique<DxfFileHandler>(),
					 std::make_unique<EventHandler>());
	
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
