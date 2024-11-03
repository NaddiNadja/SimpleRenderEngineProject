#include "AsteroidController.h"
#include <iostream>

#include "Engine/MyEngine.h"

namespace ExampleGame {

	void AsteroidController::Init() {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();

		int x = std::rand() % ((int)engine->GetScreenSize().x);
		int y = std::rand() % ((int)engine->GetScreenSize().y);
		std::cout << MovSpeed << std::endl;
		position = glm::vec2(x, y);
		parent->position = position;
	}

	void AsteroidController::Update(float deltaTime) {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();

		parent->rotation += RotSpeed * deltaTime;
		parent->position = parent->position + MovDirection * MovAmount * MovSpeed * deltaTime; // glm::sin(MovSpeed * engine->GetTime());
	}

	void AsteroidController::KeyEvent(SDL_Event& e) {
	
	}
}