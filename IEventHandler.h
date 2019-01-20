#pragma once

class SdlEngine;

struct IEventHandler
{
	virtual void Handle(SdlEngine* engine) = 0;
};
