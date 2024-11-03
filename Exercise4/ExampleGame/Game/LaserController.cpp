#include "LaserController.h"
#include <iostream>

#include "Engine/MyEngine.h"

namespace ExampleGame {
	void LaserController::Init() {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();

		float rotation = parent->rotation + 270;
		if (rotation > 360) rotation -= 360;
		MovDirection.x = -glm::cos(rotation * 0.0174532925);
		MovDirection.y = -glm::sin(rotation * 0.0174532925);
		parent->position = parent->position + MovDirection * MovAmount * MovSpeed * 0.3f;
	}

	void LaserController::Update(float deltaTime) {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();
		
		parent->position = parent->position + MovDirection * MovAmount * MovSpeed * deltaTime;
		lifetime += deltaTime;

		if (lifetime > 2) {
			parent->deleted = true;
		}
	}

	void LaserController::KeyEvent(SDL_Event& e) {

	}
}