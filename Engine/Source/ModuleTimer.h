#ifndef __ModuleTimer_H__
#define __ModuleTimer_H__

#include "Module.h"
#include "DirectXTex.h"
#include "SDL/include/SDL.h"
#include <GL/glew.h>

using namespace DirectX;

class ModuleTimer : public Module
{
public:

	ModuleTimer();
	virtual ~ModuleTimer();
	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

	float delta_time = 0.0f;
	bool running;
	Uint32 lastTime;

private:
};

#endif // __ModuleTimer_H__