
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H 

#include "Window.hpp"
#include <vector>

namespace editor
{
    /* The event manager handles global events and sends them to the correct instances as well as manage windows */
    class EventManager
    {
    public: 

        static EventManager& GetInstance() 
        {
            static EventManager eventManager; 

            return eventManager;
        }

        void Initialise(); 

        void Quit(); 

        void HandleEvents();

        // Register a window to be known by the internal system
        // If important is true the window will be able to keep the application open if its open.
        void RegisterWindow(Window* window, bool important = true); 
        
        // returns true if any windows required to keep program execution running are open. 
        bool IsRunning(); 

    private: 

        EventManager() {} 

        EventManager(const EventManager&) = delete;
        EventManager& operator=(const EventManager&) = delete;

        std::vector<std::pair<Window*, bool>> m_RegisteredWindows; 

    };
}


#endif // EVENTMANAGER_H