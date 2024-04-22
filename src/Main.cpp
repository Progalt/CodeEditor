#include <cstdio>
#include <SDL2/SDL.h>
#include "Core/Logger.hpp"
#include "Core/Window.hpp"
#include "Core/EventManager.hpp"
#include "RHI/Device.hpp"
#include "RHI/Swapchain.hpp"

int main(int argc, char* argv[]) 
{
	// Initial setup
	editor::Logger::SetSeverityThreshold(editor::Severity::Info);
	editor::EventManager::GetInstance().Initialise();

	editor::Window window; 
	window.Create("Code Editor", 1280, 720, editor::WindowContext::OpenGL);

	editor::EventManager::GetInstance().RegisterWindow(&window);

	std::shared_ptr<rhi::Device> device = rhi::Device::CreateDevice();
	std::shared_ptr<rhi::Swapchain> swapchain; 

	while (editor::EventManager::GetInstance().IsRunning()) 
	{
		editor::EventManager::GetInstance().HandleEvents(); 
	}

	rhi::Device::DestroyDevice(device);

	editor::EventManager::GetInstance().Quit();
	return 0; 
}