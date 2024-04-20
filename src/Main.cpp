#include <cstdio>
#include <SDL2/SDL.h>
#include "Core/Logger.hpp"


int main(int argc, char* argv[]) 
{
	editor::Logger::SetSeverityThreshold(editor::Severity::Info);
	
	editor::Logger::Print(editor::Severity::Info, "ahhs {}", 90);
	editor::Logger::Warning("Test, {}", 78);

	editor::Logger::Fatal("AHHHhhhhh");


	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = SDL_CreateWindow("Code Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

	bool open = true;

	while (open) 
	{
		SDL_Event evnt; 
		while(SDL_PollEvent(&evnt)) 
		{
			switch(evnt.type) 
			{
				case SDL_QUIT: open = false; break;
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0; 
}