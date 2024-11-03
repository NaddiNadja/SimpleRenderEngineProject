#include "MyEngine.h"

#include <random>

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "GameObject.h"



namespace MyEngine {
	glm::vec2 window_size;
	int Engine::GetScreenWidth() {
		// getting the terminal size is a relative expensive operation, so we use two common tricks:
		// - we read it only one time, and save the result (caching)
		// - we only do the read if someone asks for it (lazy evaluation)
		if (screen_w == -1)
			screen_w = int(window_size.x);

		return screen_w;
	}

	int Engine::GetScreenHeight() {
		// getting the terminal size is a relative expensive operation, so we use two common tricks:
		// - we read it only one time, and save the result (caching)
		// - we only do the read if someone asks for it (lazy evaluation)
		if (screen_h == -1)
			screen_h = int(window_size.y);

		return screen_h;
	}

	void Engine::Init(glm::vec2& window_size) {
		w_s = window_size;
		// initializes random generator
		std::srand(std::time(nullptr)); 
	}

	void Engine::ProcessEvents(SDL_Event& event) {
		switch (event.key.keysym.sym) {
			case SDLK_w:
				input = SDLK_w;
				break;
			case SDLK_s:
				input = SDLK_s;
				break;
			case SDLK_a:
				input = SDLK_a;
				break;
			case SDLK_d:
				input = SDLK_d;
				break;
			case SDLK_2:
				input = SDLK_2;
				break;
			case SDLK_1:
				input = SDLK_1;
				break;
			default:
				break;
		}
	}

	void Engine::Update() {
		++frame;
	}

	void Engine::Render() {
		/*if (b_show_debug_window)
		{
			std::cout << " Computation(ms) : " << GetTimeComputationMs()	<< "\t+" << std::endl;
			std::cout << " Elapsed(ms)     : " << GetTimeElapsedMs()		<< "\t+" << std::endl;
			std::cout << " FPS             : " << GetFPS()					<< "\t+" << std::endl;
			std::cout << "+++++++++++++++++++++++++++++++++";
		}*/
	}
}
