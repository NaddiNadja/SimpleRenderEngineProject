#include "PlayerController.h"
#include "LaserController.h"
#include "ComponentRendererSprite.h"

#include "Engine/MyEngine.h"

namespace ExampleGame {
	void PlayerController::Init() {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();

		parent->position = engine->GetScreenSize() / 2.f;
		parent->wraps = true;
	}

	void PlayerController::Update(float deltaTime) {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();

		parent->rotation += RotSpeed * deltaTime;
		if (parent->rotation < 0) {
			parent->rotation += 360;
		} else if (parent->rotation > 360) {
			parent->rotation -= 360;
		}
		std::cout << parent->rotation << std::endl;


		glm::vec2 newPosition = parent->position + MovDirection * MovAmount * MovSpeed * deltaTime;
		if (newPosition.x < 0) {
			newPosition.x += engine->GetScreenSize().x;
		}
		if (newPosition.x > engine->GetScreenSize().x) {
			newPosition.x -= engine->GetScreenSize().x;
		}
		if (newPosition.y < 0) {
			newPosition.y += engine->GetScreenSize().y;
		}
		if (newPosition.y > engine->GetScreenSize().y) {
			newPosition.y -= engine->GetScreenSize().y;
		}

		parent->position = newPosition;

		//parent->position = basePos + MovDirection * MovAmount * MovSpeed * engine->GetTime(); // glm::sin(MovSpeed * engine->GetTime());
	}

	void PlayerController::KeyEvent(SDL_Event& e) {
		switch (e.key.keysym.sym) {
		case SDLK_w:
			if (e.key.type == ::SDL_KEYDOWN) {
				MovDirection.y = 1;
			}
			else {
				MovDirection.y = 0;				
			}
			break;
		case SDLK_s:
			if (e.key.type == ::SDL_KEYDOWN) {
				MovDirection.y = -1;
			}
			else {
				MovDirection.y = 0;
			}
			break;
		case SDLK_a:
			if (e.key.type == ::SDL_KEYDOWN) {
				MovDirection.x = -1;
			}
			else {
				MovDirection.x = 0;
			}
			break;
		case SDLK_d:
			if (e.key.type == ::SDL_KEYDOWN) {
				MovDirection.x = 1;
			}
			else {
				MovDirection.x = 0;
			}
			break;
		case SDLK_e:
			if (e.key.type == ::SDL_KEYDOWN) {
				RotSpeed = -100;
			}
			else {
				RotSpeed = 0;
			}
			break;
		case SDLK_q:
			if (e.key.type == ::SDL_KEYDOWN) {
				RotSpeed = 100;
			}
			else {
				RotSpeed = 0;
			}
			break;
		case SDLK_SPACE:
			if (e.key.type == ::SDL_KEYDOWN) {
				MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
				MyEngine::GameObject* parent = GetGameObject();


				auto laserObject = engine->CreateGameObject("Laser");
				auto laserController = std::shared_ptr<LaserController>(new LaserController());
				auto laserRenderer = std::make_shared<ComponentRendererSprite>();
				laserObject->AddComponent(laserController);
				laserObject->AddComponent(laserRenderer);
				laserRenderer->sprite = engine->atlas->get("laserGreen08.png");

				laserObject->position = parent->position;
				laserObject->rotation = parent->rotation;
				laserObject->Init();

				std::cout << "pew pew" << std::endl;
			} else {
				std::cout << "no pew pew" << std::endl;
			}
		default:
			break;
		}
	}
}