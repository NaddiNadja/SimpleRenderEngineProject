#pragma once

#include <random>

#include "Engine/Component.h"

namespace ExampleGame {
	class AsteroidController : public MyEngine::Component {
		const float RotSpeed = (std::rand() % 100) + 50;
		const float MovSpeed = (std::rand() % 5) + 1;
		const float MovAmount = 20;
		
		const glm::vec2 MovDirection = glm::vec2(0, -1);

	public:
		glm::vec2 position;
		float rotaiton;

		void Init() override;
		void Update(float) override;
		void KeyEvent(SDL_Event& e) override;
	};
}