#include <cstdio>
#include "Core/Logger.hpp"
#include "Core/Window.hpp"
#include "Core/EventManager.hpp"


int main(int argc, char* argv[]) 
{
	// Initial setup
	editor::Logger::SetSeverityThreshold(editor::Severity::Info);
	editor::EventManager::GetInstance().Initialise();

	editor::Window window; 
	window.Create("Code Editor", 1280, 720, editor::WindowContext::OpenGL, editor::WindowStyling::AeroBorderless);

	editor::EventManager::GetInstance().RegisterWindow(&window);


	while (editor::EventManager::GetInstance().IsRunning()) 
	{
		editor::EventManager::GetInstance().HandleEvents(); 
	}


	editor::EventManager::GetInstance().Quit();
	return 0; 
}