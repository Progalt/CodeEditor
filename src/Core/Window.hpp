
#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <string>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <dwmapi.h>

#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#endif

#pragma comment (lib, "Dwmapi")

#endif // _WIN32

namespace editor
{
	enum class WindowContext
	{
		None, 
		OpenGL, 
		Metal, 
		Vulkan,
		DirectX = None, 

	};

	enum class WindowStyling
	{
		None = 0, 
		PreferDark = 1 << 0,
		AeroBorderless = 1 << 1, // Windows Only
	};

	inline WindowStyling operator|(WindowStyling lh, WindowStyling rh)
	{
		return static_cast<WindowStyling>(
				static_cast<int>(lh) | 
				static_cast<int>(rh)
			);
	}

	inline bool operator&(WindowStyling style, WindowStyling mask)
	{
		return (static_cast<int>(style) & static_cast<int>(mask));
	}

	/* Base Window class. Creates and manages a window and its events as well as OpenGL context if using OpenGL*/
	class Window
	{
	public:

		~Window(); 

		// Close the windows
		void Close(); 
		
		// Create and initialise this window
		void Create(const std::string& title, const uint32_t width, const uint32_t height, WindowContext windowContext, WindowStyling styling = WindowStyling::None); 

		// Handle events associated to this window
		void HandleWindowEvents(); 
		
		void SetTitle(const std::string& title);
		
		/* These are readonly. */

		const uint32_t GetWidth() const { return m_Width; }
		const uint32_t GetHeight() const { return m_Height; }

		const std::string& GetTitle() const { return m_Title; }

		const bool IsOpen() const { return !glfwWindowShouldClose(m_Window); }

#ifdef _WIN32
		HWND GetHWND();
#endif // _WIN32

	private:

		GLFWwindow* m_Window; 

		uint32_t m_Width = 0; 
		uint32_t m_Height = 0; 


		std::string m_Title = "";

		uint32_t m_WindowID = 0;

	};
}

#endif // WINDOW_H 