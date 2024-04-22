
#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>

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

	/* Base Window class. Creates and manages a window and its events as well as OpenGL context if using OpenGL*/
	class Window
	{
	public:

		~Window(); 

		// Close the windows
		void Close(); 
		
		// Create and initialise this window
		void Create(const std::string& title, const uint32_t width, const uint32_t height, WindowContext windowContext); 

		// Handle events associated to this window
		void HandleWindowEvents(SDL_Event* evnt); 
		
		
		/* These are readonly. */

		const uint32_t GetWidth() const { return m_Width; }
		const uint32_t GetHeight() const { return m_Height; }

		const std::string& GetTitle() const { return m_Title; }

		const bool IsOpen() const { return m_IsOpen; }

	private:

		SDL_Window* m_Window; 

		SDL_GLContext m_Context;

		uint32_t m_Width = 0; 
		uint32_t m_Height = 0; 

		bool m_IsOpen = false; 

		std::string m_Title = "";

		uint32_t m_WindowID = 0;

	};
}

#endif // WINDOW_H 