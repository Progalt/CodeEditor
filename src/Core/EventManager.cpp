
#include "EventManager.hpp"
#include <SDL2/SDL.h>

namespace editor
{   

    void EventManager::Initialise()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
    }

    void EventManager::Quit()
    {
        SDL_Quit(); 
    }

    void EventManager::RegisterWindow(Window* window, bool important) 
    {
        m_RegisteredWindows.push_back({ window, important });
    }

    bool EventManager::IsRunning()
    {
        bool open = false; 

        for (auto& win : m_RegisteredWindows)
            if (win.first->IsOpen() && win.second)
                open = true; 

        return open; 
    }

    void EventManager::HandleEvents()
    {
        SDL_Event evnt; 
        while (SDL_PollEvent(&evnt)) 
        {
            for (auto& win : m_RegisteredWindows)
            {
                win.first->HandleWindowEvents(&evnt);
            }

            
        }

    }
}