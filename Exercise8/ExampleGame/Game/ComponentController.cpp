#include "ComponentController.h"

#include "glm/glm.hpp"
#include "SDL.h"
#include "Engine/GameObject.h"
#include "Engine/MyEngine.h"

#include "Engine/Components/ComponentPhysicsBody.h"

void ComponentController::Init(rapidjson::Value& serializedData) {
	// TODO load necessary data (linear velocity, inpulse strength, etc) and add it to `scene.json`
	mov_speed = serializedData["movSpeed"].GetFloat();
	impulseStrength = serializedData["impStrength"].GetFloat();


	auto gameObject = GetGameObject().lock();
	auto body = gameObject->FindComponent<ComponentPhysicsBody>().lock();

	body->setLinearVelocity(glm::vec2(mov_speed, 0));
}

void ComponentController::Update(float deltaTime) {
	// TODO, if you need to do anything here
}

void ComponentController::KeyEvent(SDL_Event& event) {
	// TODO listen for spacebar
	if (event.key.type == ::SDL_KEYUP) {
		return;
	}

	auto gameObject = GetGameObject().lock();
	auto body = gameObject->FindComponent<ComponentPhysicsBody>().lock();

	switch (event.key.keysym.sym) {
	case SDLK_SPACE:
		body->addImpulse(glm::vec2(0, impulseStrength));
		break;
	case SDLK_s:	
		body->setLinearVelocity(glm::vec2(mov_speed, 0));
		break;
	default:
		break;
	}
}

void ComponentController::OnCollisionStart(ComponentPhysicsBody* other) {
	// TODO gameOver on touching pipes, despawn coins
	auto otherParent = other->GetGameObject().lock();
	std::cout << otherParent->GetName().find("Coin") << std::endl;
	std::cout << "collide" << " " << otherParent->GetName() << std::endl;
	if (otherParent->GetName().find("Coin") != std::string::npos) {
		auto engine = MyEngine::Engine::GetInstance();
		engine->DeregisterPhysicsComponent(other);
		engine->DestroyGameObject(otherParent.get());
	} else if (otherParent->GetName().find("Wall") != std::string::npos) {
		auto gameObject = GetGameObject().lock();
		auto body = gameObject->FindComponent<ComponentPhysicsBody>().lock();
		std::cout << "womp womp" << std::endl;
		body->setLinearVelocity(glm::vec2(0, 0));
	}
}