#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "Engine/MyEngine.h"

#include "Game/PlayerController.h"
#include "Game/LaserController.h"
#include "Game/AsteroidController.h"
#include "Game/ComponentRendererSprite.h"

void InitGame();
void ProcessEvents(SDL_Event& event);
void Update(float deltaTime);
void Render();

MyEngine::Engine engine;

glm::vec2 window_size = glm::vec2(1280, 720);
sre::SDLRenderer renderer;
sre::Camera camera;
std::shared_ptr<sre::SpriteAtlas> atlas;

int main() {
	renderer.frameRender = Render;
	renderer.frameUpdate = Update;
	renderer.keyEvent = ProcessEvents;

	renderer.setWindowSize(window_size);
	renderer.init();
	camera.setWindowCoordinates();

	engine.atlas = sre::SpriteAtlas::create("data/asteroids.json", "data/asteroids.png");

	auto playerObject = engine.CreateGameObject("Player");
	auto playerController = std::shared_ptr<ExampleGame::PlayerController>(new ExampleGame::PlayerController());
	auto playerRenderer = std::make_shared<ExampleGame::ComponentRendererSprite>();
	playerObject->AddComponent(playerController);
	playerObject->AddComponent(playerRenderer);
	playerRenderer->sprite = engine.atlas->get("playerShip1_green.png");
	playerObject->radius = 40;

	std::string asteroidFilenames[] = { "meteorGrey_small1.png", "meteorGrey_med1.png", "meteorGrey_big4.png" };
	int asteroidRadius[] = { 20, 35, 60 };

	for (int i = 0; i  < 5; i++) {
		auto asteroidObject = engine.CreateGameObject("Asteroid");
		auto asteroidController = std::shared_ptr<ExampleGame::AsteroidController>(new ExampleGame::AsteroidController());
		auto componentRenderer = std::make_shared<ExampleGame::ComponentRendererSprite>();
		asteroidObject->AddComponent(asteroidController);
		asteroidObject->AddComponent(componentRenderer);
		int index = std::rand() % 3;
		std::string name = asteroidFilenames[index];
		componentRenderer->sprite = engine.atlas->get(name);
		int radius = asteroidRadius[index];
		asteroidObject->radius = radius;
	}
	
	engine.Init(); 


	renderer.startEventLoop();
}

void ProcessEvents(SDL_Event& event) { 
	engine.ProcessEvents(event);
}

void Update(float deltaTime) {
	engine.Update(deltaTime);
}

void Render() {
	engine.Render();
}