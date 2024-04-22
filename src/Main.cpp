#include <cstdio>
#include "Core/Logger.hpp"
#include "Core/Window.hpp"
#include "Core/EventManager.hpp"
#include "Painter/Painter.hpp"



int main(int argc, char* argv[]) 
{
	// Initial setup
	editor::Logger::SetSeverityThreshold(editor::Severity::Info);
	editor::EventManager::GetInstance().Initialise();

	editor::Window window; 
	window.Create("Code Editor", 1280, 720, editor::WindowContext::OpenGL, editor::WindowStyling::AeroBorderless);
	window.SetHitTestDragRect({ 0, 0, 64, 64 });

	editor::EventManager::GetInstance().RegisterWindow(&window);

	painter::Canvas canvas; 


	while (editor::EventManager::GetInstance().IsRunning()) 
	{
		editor::EventManager::GetInstance().HandleEvents(); 

		window.Present();
	}


	editor::EventManager::GetInstance().Quit();
	return 0; 
}