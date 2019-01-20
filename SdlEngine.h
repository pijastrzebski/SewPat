#pragma once

#include "IDrawer.h"
#include "IParser.h"
#include "IFileHandler.h"
#include "SDL_render.h"
#include "IEventHandler.h"

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>

enum class EngineState
{
	START = 0,
	STOP,
	PAUSE
};

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Point;
struct SDL_Rect;

struct Texture
{
	enum EName
	{
		DROP = 0,
		DRAW,
		SAVE,
		QUIT
	};

	Texture(const EName& eName, SDL_Texture* texture, const SDL_Rect& rect) :
		m_eName(eName),
		m_texture(texture),
		m_rect(rect){}

	EName m_eName;
	SDL_Texture* m_texture;
	SDL_Rect m_rect;
};

class SdlEngine
{
	friend class EventHandler;
public:
	SdlEngine(std::unique_ptr<IParser> parser,
		      std::unique_ptr<IDrawer> drawer,
		      std::unique_ptr<IFileHandler> fileHandler,
		      std::unique_ptr<IEventHandler> eventHandler) noexcept;
	~SdlEngine();

	SdlEngine& Init() const;
	int StartLoop();	

	SdlEngine& CreateMainWindow();
	SdlEngine& CreateRenderer();
	SdlEngine& InitImgSupport();
	SdlEngine& CreateSurface(const std::string& fileName);
	SdlEngine& CreateBufferedTextureFromSurface();
	SDL_Texture* CreateTexture(const std::string& fileName, SDL_Renderer* renderer);
	void SetTextureColor(SDL_Texture* texture, uint8_t r, uint8_t g, uint8_t b);
	
	SdlEngine& CreateBufferedTexture(const std::string& fileName);
	void CreateDrawWindow();
	void SetPosAndScaleForBufferedTexture(int x, int y, int scale);
	void RenderBufferedTexture(SDL_Renderer* renderer) const;
	void RenderTexture(SDL_Renderer* renderer, Texture& texture) const;
	void SetBufferedTextureSize();

protected:
	std::vector<Texture> m_textureMap;

private:
	std::unique_ptr<IParser>       m_parser;
	std::unique_ptr<IDrawer>       m_drawer;
	std::unique_ptr<IFileHandler>  m_fileHandler;
	std::unique_ptr<IEventHandler> m_eventHandler;

	int m_mouseUpX;
	int m_mouseUpY;
	int m_mouseDownX;
	int m_mouseDownY;
	bool m_isMouseButtonPressed;

	std::string m_title;
	int m_posX;
	int m_posY;
	int m_width;
	int m_height;
	int m_deltaX;
	int m_deltaY;

	uint32_t m_mainWindowID;
	uint32_t m_drawWindowID;

	int m_bufferedTextureWidth;
	int m_bufferedTextureHeight;

	EngineState m_state;

	SDL_Event m_event;
	SDL_Window *m_mainWindow;
	SDL_Window *m_drawWindow;
	SDL_Renderer *m_renderer;
	SDL_Surface *m_surface;
	SDL_Texture *m_bufferedTexture;
	std::vector<SDL_Point> m_bufferedPoints;
};

