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
		//engine->CreateDrawWindow();
		break;
	case SDL_KEYUP:
		std::cout << "Key released\n";
		break;
	case SDL_DROPFILE:
		std::string filePath = engine->m_event.drop.file;
		std::cout << "Dropped file dir: " << filePath << '\n';	

		engine->m_parser->Read(filePath);
		auto parseResults = dynamic_cast<SSZ_ParserResults*>(engine->m_parser->GetResults());
		if (parseResults != nullptr)
		{
			engine->m_calculatedResults = std::move(engine->m_calculator->Calculate(*parseResults));
			engine->m_isCalculationDone = true;
		}
		else
		{
			std::clog << "Error: Couldn't get results from parser!\n";
		}
		break;
	}

	// handle mouse events
	if (engine->m_event.type == SDL_MOUSEBUTTONUP)
	{
		engine->m_isMouseButtonPressed = false;
	}

	if (engine->m_event.type == SDL_MOUSEMOTION && !engine->m_isMouseButtonPressed)
	{
		// track current mouse pos
		SDL_GetMouseState(&engine->m_mouseUpX, &engine->m_mouseUpY);
		std::clog << "X: " << engine->m_mouseUpX << " Y:" << engine->m_mouseUpY << '\n';
	}

	if (engine->m_event.type == SDL_MOUSEBUTTONDOWN)
	{
		engine->m_isMouseButtonPressed = true;

		for (auto& t : engine->m_textureMap)
		{
			switch (t.m_eName)
			{
			case Texture::QUIT:
				if ((engine->m_mouseUpX > t.m_rect.x) &&
					(engine->m_mouseUpX < t.m_rect.x + t.m_rect.w - 10) &&
					(engine->m_mouseUpY > t.m_rect.y) &&
					(engine->m_mouseUpY < t.m_rect.y + t.m_rect.h - 10)
					)
				{
					std::clog << "Clicked on Quit button\n";
					engine->m_state = EngineState::STOP;
				}
				break;
			case Texture::DRAW:
				if ((engine->m_mouseUpX > t.m_rect.x) &&
					(engine->m_mouseUpX < t.m_rect.x + t.m_rect.w - 10) &&
					(engine->m_mouseUpY > t.m_rect.y) &&
					(engine->m_mouseUpY < t.m_rect.y + t.m_rect.h - 10)
					)
				{
					std::clog << "Clicked on Draw button\n";
				}
				break;
			case Texture::DROP:
				if ((engine->m_mouseUpX > t.m_rect.x) &&
					(engine->m_mouseUpX < t.m_rect.x + t.m_rect.w - 10) &&
					(engine->m_mouseUpY > t.m_rect.y) &&
					(engine->m_mouseUpY < t.m_rect.y + t.m_rect.h - 10)
					)
				{
					std::clog << "Clicked on Drop button\n";
				}
				break;
			case Texture::SAVE:
			{
				if ((engine->m_mouseUpX > t.m_rect.x) &&
					(engine->m_mouseUpX < t.m_rect.x + t.m_rect.w - 10) &&
					(engine->m_mouseUpY > t.m_rect.y) &&
					(engine->m_mouseUpY < t.m_rect.y + t.m_rect.h - 10)
					)
				{
					std::clog << "Clicked on Save button\n";
					if (engine->m_isCalculationDone)
					{
						std::clog << "Start generating dxf\n";
						engine->m_fileHandler->WriteToFile(engine->m_calculatedResults);
						std::clog << "Dxf file generated successfully!\n";
					}
				}
			}
				break;
			default:
				break;
			}
		}
	}

	if (engine->m_event.type == SDL_MOUSEMOTION && engine->m_isMouseButtonPressed)
	{
		SDL_GetMouseState(&engine->m_mouseDownX, &engine->m_mouseDownY);
	}

	// handle window events
	if (engine->m_event.window.windowID == engine->m_mainWindowID)
	{
		switch (engine->m_event.window.event)
		{
		case SDL_WINDOWEVENT_CLOSE:
			std::clog << "Close Main Window event\n";
			engine->m_state = EngineState::STOP;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (engine->m_event.window.event)
		{
		case SDL_WINDOWEVENT_CLOSE:
			std::clog << "Hide Draw Window event\n";
			SDL_HideWindow(engine->m_drawWindow);
			break;
		default:
			break;
		}
	}

	if (engine->m_event.type == SDL_MOUSEMOTION)
	{
		// add texture fancy effects
		for (auto& t : engine->m_textureMap)
		{
			if ((engine->m_mouseUpX > t.m_rect.x) &&
				(engine->m_mouseUpX < t.m_rect.x + t.m_rect.w - 10) &&
				(engine->m_mouseUpY > t.m_rect.y) &&
				(engine->m_mouseUpY < t.m_rect.y + t.m_rect.h - 10)
				)
			{
				engine->SetTextureColor(t.m_texture, 255, 215, 0);
			}
			else
			{
				engine->SetTextureColor(t.m_texture, 255, 255, 255);
			}
		}
	}
}
