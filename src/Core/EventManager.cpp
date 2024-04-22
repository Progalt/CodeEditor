
#include "EventManager.hpp"
#include <GLFW/glfw3.h>
#include "Logger.hpp"

namespace editor
{   

    void EventManager::Initialise()
    {
        if (glfwInit() == GLFW_FALSE) 
        {
            Logger::Fatal("Failed to initialise GLFW");
        }
    }

    void EventManager::Quit()
    {
        glfwTerminate();
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
        glfwPollEvents();

    }
}