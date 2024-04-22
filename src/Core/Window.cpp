
#include "Window.hpp"
#include "Logger.hpp"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace editor 
{

#ifdef _WIN32

    // https://discourse.glfw.org/t/making-a-custom-titlebar/2392/6

    WNDPROC original_proc;

    LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_NCCALCSIZE:
        {
            // Remove the window's standard sizing border
            if (wParam == TRUE && lParam != NULL)
            {
                NCCALCSIZE_PARAMS* pParams = reinterpret_cast<NCCALCSIZE_PARAMS*>(lParam);
                pParams->rgrc[0].top += 1;
                pParams->rgrc[0].right -= 2;
                pParams->rgrc[0].bottom -= 2;
                pParams->rgrc[0].left += 2;
            }
            return 0;
        }
        case WM_NCPAINT:
        {
            // Prevent the non-client area from being painted
            return 0;
        }
        case WM_NCHITTEST:
        {
            // Expand the hit test area for resizing
            const int borderWidth = 4; // Adjust this value to control the hit test area size

            POINTS mousePos = MAKEPOINTS(lParam);
            POINT clientMousePos = { mousePos.x, mousePos.y };
            ScreenToClient(hWnd, &clientMousePos);

            RECT windowRect;
            GetClientRect(hWnd, &windowRect);

            if (clientMousePos.y >= windowRect.bottom - borderWidth)
            {
                if (clientMousePos.x <= borderWidth)
                    return HTBOTTOMLEFT;
                else if (clientMousePos.x >= windowRect.right - borderWidth)
                    return HTBOTTOMRIGHT;
                else
                    return HTBOTTOM;
            }
            else if (clientMousePos.y <= borderWidth)
            {
                if (clientMousePos.x <= borderWidth)
                    return HTTOPLEFT;
                else if (clientMousePos.x >= windowRect.right - borderWidth)
                    return HTTOPRIGHT;
                else
                    return HTTOP;
            }
            else if (clientMousePos.x <= borderWidth)
            {
                return HTLEFT;
            }
            else if (clientMousePos.x >= windowRect.right - borderWidth)
            {
                return HTRIGHT;
            }
            /*else
            {
                return HTCAPTION;
            }*/

            break;
        }
        }

        return CallWindowProc(original_proc, hWnd, uMsg, wParam, lParam);
    }

#endif

    Window::~Window()
    {
       Close(); 
    }

    void Window::Close() 
    {
        
    }

    void Window::Create(const std::string& title, const uint32_t width, const uint32_t height, WindowContext windowContext, WindowStyling styling)
    {
        
        m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

        if (!m_Window)
        {
            Logger::Fatal("Failed to create Window");
            return; 
        }

        if (windowContext == WindowContext::OpenGL)
        {
            glfwMakeContextCurrent(m_Window);
        }

        if (styling & WindowStyling::PreferDark)
        {
#ifdef _WIN32
            HWND hwnd = GetHWND();

            const BOOL darkMode = true; 

            if (FAILED(DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &darkMode, sizeof(darkMode))))
            {
                Logger::Error("Failed to set window title bar to dark mode");
            }

            glfwHideWindow(m_Window);
            glfwShowWindow(m_Window);

#endif
        }

#ifdef _WIN32
        if (styling & WindowStyling::AeroBorderless)
        {
            HWND hWnd = glfwGetWin32Window(m_Window);

            LONG_PTR lStyle = GetWindowLongPtr(hWnd, GWL_STYLE);
            lStyle |= WS_THICKFRAME;
            lStyle &= ~WS_CAPTION;
            SetWindowLongPtr(hWnd, GWL_STYLE, lStyle);

            MARGINS margins = { 0 };
            DwmExtendFrameIntoClientArea(hWnd, &margins);

            RECT windowRect;
            GetWindowRect(hWnd, &windowRect);
            int width = windowRect.right - windowRect.left;
            int height = windowRect.bottom - windowRect.top;

            original_proc = (WNDPROC)GetWindowLongPtr(hWnd, GWLP_WNDPROC);
            (WNDPROC)SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowProc));
            SetWindowPos(hWnd, NULL, 0, 0, width, height, SWP_FRAMECHANGED | SWP_NOMOVE);
        
        }
#endif

        Logger::Info("Successfully created window");   
        
    }

    void Window::HandleWindowEvents()
    {
        
    }

    void Window::SetTitle(const std::string& title)
    {
        glfwSetWindowTitle(m_Window, title.c_str());
    }

#ifdef _WIN32
    HWND Window::GetHWND()
    {
        return glfwGetWin32Window(m_Window); 
    }
#endif // _WIN32
}