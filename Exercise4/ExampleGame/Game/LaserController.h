#pragma once

#include <random>
#include "Engine/Component.h"

namespace ExampleGame {
	class LaserController : public MyEngine::Component {
		const float RotSpeed = 0;
		const float MovSpeed = 10;
		const float MovAmount = 20;

		glm::vec2 MovDirection = glm::vec2(0, 0);

	public:
		glm::vec2 position;
		float rotaiton;
		float lifetime;

		void Init() override;
		void Update(float) override;
		void KeyEvent(SDL_Event& e) override;
	};
}