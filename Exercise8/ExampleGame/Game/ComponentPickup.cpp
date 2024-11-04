#include "ComponentController.h"

#include "glm/glm.hpp"
#include "SDL.h"
#include "Engine/GameObject.h"

#include "Engine/Components/ComponentPhysicsBody.h"

void ComponentPickup::Init(rapidjson::Value& serializedData) {
	// TODO load necessary data (linear velocity, inpulse strength, etc) and add it to `scene.json`
}

void ComponentPickup::Update(float deltaTime) {
	// TODO, if you need to do anything here
}

void ComponentPickup::KeyEvent(SDL_Event& event) {
	// TODO listen for spacebar
}

void ComponentPickup::OnCollisionStart(ComponentPhysicsBody* other) {
	// TODO gameOver on touching pipes, despawn coins
	std::cout << "coin" << std::endl;
}