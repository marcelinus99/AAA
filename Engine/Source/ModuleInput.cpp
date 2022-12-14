#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"
#include "imgui_impl_sdl.h"
#include "PanelConsole.h"

ModuleInput::ModuleInput()
{
    mouseX = 0;
    mouseY = 0;
    orbitMouseMotionX = 0;
    orbitMouseMotionY = 0;
    mouseMotionX = 0;
    mouseMotionY = 0;
    wheel = 0;
}

ModuleInput::~ModuleInput()
{
}


bool ModuleInput::Init()
{
    App->editor->AddLog("Init SDL input event system");
    bool ret = true;
    SDL_Init(0);

    if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
    {
        DEBUGLOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
        ret = false;
    }

    return ret;
}

update_status ModuleInput::Update()
{
    SDL_Event sdlEvent;
    wheel = 0;
    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            return UPDATE_STOP;
        case SDL_WINDOWEVENT:
            if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
            break;
        case SDL_MOUSEMOTION:
            mouseX = sdlEvent.motion.x;
            mouseY = sdlEvent.motion.y;
            if (sdlEvent.motion.state == SDL_BUTTON_RMASK) {
                mouseMotionX = sdlEvent.motion.xrel;
                mouseMotionY = sdlEvent.motion.yrel;
                orbit = false;
            }
            else if (sdlEvent.motion.state == SDL_BUTTON_LMASK) {
                orbitMouseMotionX = sdlEvent.motion.xrel;
                orbitMouseMotionY = sdlEvent.motion.yrel;
                orbit = true;
            }
            else {
                mouseMotionX = 0;
                mouseMotionY = 0;
                orbitMouseMotionX = 0;
                orbitMouseMotionY = 0;
                orbit = false;
            }
            break;
        case SDL_MOUSEWHEEL:
            wheel = sdlEvent.wheel.y;
            break;
        case SDL_DROPFILE:
            App->editor->AddLog("File dropped");
            App->renderer->DropFile(sdlEvent.drop.file);
            break;
        }
        keyboard = SDL_GetKeyboardState(NULL);
    }
    return UPDATE_CONTINUE;
}

bool ModuleInput::CleanUp()
{
    App->editor->AddLog("Quitting SDL input event subsystem");
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
    return true;
}

void ModuleInput::GetMousePosition(int& x, int& y) {
    x = mouseX;
    y = mouseY;
}

void ModuleInput::GetMouseMotion(int& x, int& y) {
    x = mouseMotionX;
    y = mouseMotionY;
}

void ModuleInput::GetOrbitMouseMotion(int& x, int& y) {
    x = orbitMouseMotionX;
    y = orbitMouseMotionY;
}

void ModuleInput::GetWheel(int& w) {
    w = wheel;
}
