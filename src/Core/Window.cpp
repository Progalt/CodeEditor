
#include "Window.hpp"
#include "Logger.hpp"

namespace editor 
{

    Window::~Window()
    {
       Close(); 
    }

    void Window::Close() 
    {
        if (m_Window && m_IsOpen) 
        {
            SDL_DestroyWindow(m_Window);
            m_IsOpen = false; 
            Logger::Info("Closed Window");
        }
    }

    void Window::Create(const std::string& title, const uint32_t width, const uint32_t height)
    {
        m_Window = SDL_CreateWindow(
            title.c_str(),  
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
            width, height, 
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
        );

        if (!m_Window) 
        {
            Logger::Fatal("Failed to create Window: {}", SDL_GetError());
            return; 
        }

        
        
        // Query the size from the window itself instead of using the parameters. Since it might've changed
        int w, h; 
        SDL_GetWindowSize(m_Window, &w, &h);

        m_Width = static_cast<uint32_t>(w);
        m_Height = static_cast<uint32_t>(h);

        m_Title = title; 

        m_WindowID = SDL_GetWindowID(m_Window);

        m_IsOpen = true; 


         Logger::Info("Successfully created window");   
        
    }

    void Window::HandleWindowEvents(SDL_Event* evnt)
    {
        if (evnt->type != SDL_WINDOWEVENT )
            return; 

        if (evnt->window.windowID != m_WindowID)
            return;

        switch(evnt->window.event) 
        {
        case SDL_WINDOWEVENT_CLOSE: 
            Close(); 
            break; 
        };
    }
}