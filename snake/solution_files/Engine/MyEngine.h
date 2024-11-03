#pragma once

#include <chrono>

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

class GameObject;

namespace MyEngine {
	class Engine {

	public:
		glm::vec2 w_s;
		const std::chrono::duration<double> MAX_FRAME_TIME = std::chrono::duration<double>(1 / 60.0);

		inline float GetFPS() { return 1.0 / time_elapsed.count(); }
		inline float GetTimeElapsedMs() { return 1000 * time_elapsed.count(); }
		inline float GetTimeComputationMs() { return 1000 * time_computation.count(); }
		int GetScreenWidth();
		int GetScreenHeight();

		// Components needs access to certain functionality of the Engine.
		// Pointer-less solution 1: static access
		inline int GetFrame() { return frame; }

		std::chrono::time_point<std::chrono::steady_clock>	time_start;
		std::chrono::time_point<std::chrono::steady_clock>	time_end;
		std::chrono::time_point<std::chrono::steady_clock>	time_end_computation;
		std::chrono::duration<double>						time_elapsed;
		std::chrono::duration<double>						time_computation;
		int frame;

		unsigned char input = -1;
		bool b_show_debug_window = false;

		int screen_w = -1;
		int screen_h = -1;

		void Init(glm::vec2& window_size);
		void ProcessEvents(SDL_Event& event);
		void Update();
		void Render();
	};
}