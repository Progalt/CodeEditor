
#include "EventManager.hpp"
#include <SDL2/SDL.h>
#include "Logger.hpp"

namespace editor
{   

    void EventManager::Initialise()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
        {
            Logger::Fatal("Failed to initialise SDL2: {}", SDL_GetError());
        }
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

        // This can get quite slow if there are too many windows. 
        // I don't think there should be more than approx 3 open
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
            // Pass Window events to the Windows
            for (auto& win : m_RegisteredWindows)
            {
                win.first->HandleWindowEvents(&evnt);
            }

            // Now handle other events

            switch(evnt.type) 
            {

            }


        }

    }
}