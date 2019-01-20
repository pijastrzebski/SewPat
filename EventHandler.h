#pragma once

#include "IEventHandler.h"
#include "SdlEngine.h"

class EventHandler : public IEventHandler
{
public:
	EventHandler();
	~EventHandler();

	void Handle(SdlEngine* engine);
	
};

