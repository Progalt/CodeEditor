
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
            if (m_Context)
            {
                SDL_GL_DeleteContext(m_Context);
            }

            SDL_DestroyWindow(m_Window);
            m_IsOpen = false; 
            Logger::Info("Closed Window");
        }
    }

    void Window::Create(const std::string& title, const uint32_t width, const uint32_t height, WindowContext windowContext)
    {
        uint32_t flags = SDL_WINDOW_SHOWN; 

        // Pre window setup for graphics APIs. 

        if (windowContext == WindowContext::OpenGL)
        {
            // Set this to share resources
            SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            
            // Add the flags to the window
            flags |= SDL_WINDOW_OPENGL;

        }

        if (windowContext == WindowContext::Metal)
        {
            flags |= SDL_WINDOW_METAL;
        }

        if (windowContext == WindowContext::Vulkan)
        {
            flags |= SDL_WINDOW_VULKAN; 
        }

        m_Window = SDL_CreateWindow(
            title.c_str(),  
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
            width, height, 
            flags
        );

        if (!m_Window) 
        {
            Logger::Fatal("Failed to create Window: {}", SDL_GetError());
            return; 
        }

        if (windowContext == WindowContext::OpenGL)
        {
            // For OpenGL we have to create a context

            m_Context = SDL_GL_CreateContext(m_Window);
            SDL_GL_MakeCurrent(m_Window, m_Context);

            if (!m_Context)
            {
                Logger::Fatal("Failed to create OpenGL Context: {}", SDL_GetError());
            }
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