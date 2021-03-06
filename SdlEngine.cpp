#include "SdlEngine.h"
//#include <SDL_ttf.h>
#include "XlsxParser.h"
#include "SewPatternDrawer.h"

#include <iostream>
#include <exception>
#include <string>
#include <filesystem>
#include <future>

SdlEngine& SdlEngine::Init() const
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));		
	}
	return *const_cast<SdlEngine*>(this);
}

int SdlEngine::StartLoop()
{
	m_state = EngineState::START;

	// prepare menu textures			//TODO: Create texture init method
	m_textureMap.emplace_back(Texture::DROP, CreateTexture("drop.png", m_renderer), SDL_Rect{});
	m_textureMap.emplace_back(Texture::DRAW, CreateTexture("draw.png", m_renderer), SDL_Rect{ m_width / 2, 0 });
	m_textureMap.emplace_back(Texture::SAVE, CreateTexture("save.png", m_renderer), SDL_Rect{ 0, m_height / 2 });
	m_textureMap.emplace_back(Texture::QUIT, CreateTexture("quit.png", m_renderer), SDL_Rect{ m_width / 2, m_height / 2 });

	while (m_state != EngineState::STOP)
	{
		while (SDL_PollEvent(&m_event))
		{
			m_eventHandler->Handle(this);
		}
		//m_parser.Read(R"(C:\Users\Piotr\Downloads\kontrukcja odzieży.xlsx)");

		// TODO: Create Render Engine
		//m_drawer.DrawLine(m_renderer);

		// draw menu
		SDL_RenderClear(m_renderer);

		for (auto& texture : m_textureMap)
		{
			RenderTexture(m_renderer, texture);
		}

		SDL_RenderPresent(m_renderer);
	}
	return 0;
}

SdlEngine& SdlEngine::CreateMainWindow()
{
	m_mainWindow = SDL_CreateWindow(m_title.c_str(),
		                        m_posX,
		                        m_posY,
		                        m_width,
		                        m_height,
								SDL_WINDOW_OPENGL |
								SDL_WINDOW_ALLOW_HIGHDPI
		);

	if (!m_mainWindow)
	{
		throw std::runtime_error("SDL_CreateWindow Error: " + std::string(SDL_GetError()));
	}

	m_mainWindowID = SDL_GetWindowID(m_mainWindow);

	return *const_cast<SdlEngine*>(this);
}

SdlEngine& SdlEngine::CreateRenderer()
{
	m_renderer = SDL_CreateRenderer(m_mainWindow,
		                            -1,
		                            SDL_RENDERER_ACCELERATED | 
									SDL_RENDERER_PRESENTVSYNC);

	if (!m_renderer)
	{
		throw std::runtime_error("SDL_CreateRenderer Error: " + std::string(SDL_GetError()));
	}

	return *const_cast<SdlEngine*>(this);
}

SdlEngine& SdlEngine::InitImgSupport()
{
	if (!IMG_Init(IMG_INIT_PNG))
	{
		throw std::runtime_error("InitImgSupport Error: " + std::string(IMG_GetError()));
	}

	return *const_cast<SdlEngine*>(this);
}

SdlEngine& SdlEngine::CreateSurface(const std::string& fileName)
{
	namespace fs = std::filesystem;

	auto path = fs::current_path().string() + R"(\..\..\rsc\png\)" + fileName;
	m_surface = IMG_Load(path.c_str());

	if (!m_surface)
	{
		throw std::runtime_error("CreateSurface Error: " + std::string(IMG_GetError()));
	}

	return *const_cast<SdlEngine*>(this);
}

SdlEngine& SdlEngine::CreateBufferedTextureFromSurface()
{
	m_bufferedTexture = SDL_CreateTextureFromSurface(m_renderer, m_surface);

	if (!m_bufferedTexture)
	{
		throw std::runtime_error("CreateTextureFromSurface Error: " + std::string(SDL_GetError()));
	}

	return *const_cast<SdlEngine*>(this);
}

SDL_Texture* SdlEngine::CreateTexture(const std::string& fileName, SDL_Renderer* renderer)
{
	namespace fs = std::filesystem;

	auto path = fs::current_path().string() + R"(\..\..\rsc\png\)" + fileName;
	auto surface = IMG_Load(path.c_str());
	if (!surface)
	{
		throw std::runtime_error("Surface Error: " + std::string(IMG_GetError()));
	}

	auto texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture)
	{
		throw std::runtime_error("CreateTextureFromSurface Error: " + std::string(SDL_GetError()));
	}
	return texture;
}

void SdlEngine::SetTextureColor(SDL_Texture* texture, uint8_t r, uint8_t g, uint8_t b)
{
	SDL_SetTextureColorMod(texture, r, g, b);
}

SdlEngine& SdlEngine::CreateBufferedTexture(const std::string& fileName)
{
	CreateSurface(fileName);
	CreateBufferedTextureFromSurface();

	return *const_cast<SdlEngine*>(this);
}

void SdlEngine::CreateDrawWindow()
{
	if (!m_drawWindow)
	{
		m_drawWindow = SDL_CreateWindow("Draw Window",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			1280,
			1024,
			SDL_WINDOW_ALLOW_HIGHDPI
		);

		if (!m_drawWindow)
		{
			throw std::runtime_error("CreateDrawWindow Error: " + std::string(SDL_GetError()));
		}

		m_drawWindowID = SDL_GetWindowID(m_mainWindow);
	}
	else
	{
		SDL_ShowWindow(m_drawWindow);
	}
}

void SdlEngine::SetPosAndScaleForBufferedTexture(int x, int y, int scale = 100)
{
	if (m_bufferedTexture)
	{
		// set texture to draw
		SDL_Rect rect{ x, y };

		if (SDL_QueryTexture(m_bufferedTexture, nullptr, nullptr, &rect.w, &rect.h))
		{
			throw std::runtime_error("SDL_QueryTexture Error: " + std::string(SDL_GetError()));
		}

		// custom scale calculation
		if (scale != 100)
		{
			auto scaledWidth = static_cast<float>(rect.w);
			scaledWidth /= 100;
			scaledWidth *= scale;
			rect.w = static_cast<int>(scaledWidth);

			auto scaledHeight = static_cast<float>(rect.h);
			scaledHeight /= 100;
			scaledHeight *= scale;
			rect.h = static_cast<int>(scaledHeight);
		}
	}
	else
	{
		throw std::runtime_error("SetPosAndScaleForBufferedTexture Error: Buffered Texture is Empty");
	}
}

void SdlEngine::RenderBufferedTexture(SDL_Renderer* renderer) const
{
	if (m_bufferedTexture)
	{
		SDL_RenderClear(renderer);

		if (SDL_RenderCopy(renderer, m_bufferedTexture, nullptr, nullptr))
		{
			throw std::runtime_error("SDL_RenderCopy Error: " + std::string(SDL_GetError()));
		}
	}
}

void SdlEngine::RenderTexture(SDL_Renderer* renderer, Texture& texture) const
{
	if (SDL_QueryTexture(texture.m_texture, nullptr, nullptr, &texture.m_rect.w, &texture.m_rect.h))
	{
		throw std::runtime_error("SetBufferedTextureSize Error: " + std::string(SDL_GetError()));
	}
	if (SDL_RenderCopy(renderer, texture.m_texture, nullptr, &texture.m_rect))
	{
		throw std::runtime_error("SDL_RenderCopy Error: " + std::string(SDL_GetError()));
	}
}

void SdlEngine::SetBufferedTextureSize()
{
	if (SDL_QueryTexture(m_bufferedTexture, nullptr, nullptr, &m_bufferedTextureWidth, &m_bufferedTextureHeight))
	{
		throw std::runtime_error("SetBufferedTextureSize Error: " + std::string(SDL_GetError()));
	}
}

SdlEngine::SdlEngine(std::unique_ptr<IParser> parser,
					 std::unique_ptr<IDrawer> drawer,
					 std::unique_ptr<IFileHandler> fileHandler,
					 std::unique_ptr<IEventHandler> eventHandler
) noexcept :
	m_parser(std::move(parser)),
	m_drawer(std::move(drawer)),
	m_fileHandler(std::move(fileHandler)),
	m_eventHandler(std::move(eventHandler)),
	m_title("SewPat App V.1.0"),
	m_posX(300),  // there's no reason why 300x300
	m_posY(300),
	m_width(500), // Fibonacci's ratio
	m_height(800),
	m_mainWindow(nullptr),
	m_renderer(nullptr),
	m_mouseUpX(0),
	m_mouseUpY(0),
	m_mouseDownX(0),
	m_mouseDownY(0),
	m_isMouseButtonPressed(false),
	m_deltaX(0),
	m_deltaY(0),
	m_mainWindowID(0),
	m_drawWindowID(0),
	m_isCalculationDone(false)
{}


SdlEngine::~SdlEngine()
{
	SDL_DestroyTexture(m_bufferedTexture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_drawWindow);
	SDL_DestroyWindow(m_mainWindow);
	IMG_Quit();
	SDL_Quit();
}
