#pragma once

#include "Engine/Component.h"

namespace ExampleGame {
	class PlayerController : public MyEngine::Component {
		float RotSpeed = 0;
		const float MovSpeed = 5;
		const float MovAmount = 20;
		glm::vec2 MovDirection = glm::vec2(0, 0);

	public:
		glm::vec2 position;
		float rotaiton;

		void Init() override;
		void Update(float) override;
		void KeyEvent(SDL_Event& e) override;
	};
}