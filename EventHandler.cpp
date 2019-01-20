#include "EventHandler.h"

#include <iostream>
#include <future>

EventHandler::EventHandler()
{
}


EventHandler::~EventHandler()
{
}

void EventHandler::Handle(SdlEngine* engine)
{
	// handle main events
	switch (engine->m_event.type)			//TODO: Create Handlers
	{
	case SDL_QUIT:
		engine->m_state = EngineState::STOP;
		break;
	case SDL_KEYDOWN:
		std::cout << "Key pressed\n";
		//m_fileHandler.WriteToFile();
		engine->CreateDrawWindow();
		break;
	case SDL_KEYUP:
		std::cout << "Key released\n";
		break;
	case SDL_DROPFILE:
		std::string filePath = engine->m_event.drop.file;
		std::cout << "Dropped file dir: " << filePath << '\n';
		auto result = std::async(std::launch::async,
			[=]() {
			engine->m_parser->Read(filePath);
		});		//TODO: Upgrade XlsxParser
				//TODO: Add SewPat Calculator
		break;
	}
}
