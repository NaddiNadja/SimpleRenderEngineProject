#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

//
#include <iostream>
#include <cstdint>

#include "Game/Player.h"
#include "Game/Score.h"
#include "Game/Collectible.h"

void InitGame();
void Update(float deltaTime);

Snake::Score		score;
Snake::Player		player;
Snake::Collectible	collectible;
//

glm::vec2 window_size = glm::vec2(800, 600);
sre::SDLRenderer renderer;
sre::Camera camera;
std::shared_ptr<sre::SpriteAtlas> atlas;

sre::Sprite sprite;

MyEngine::Engine engine;

void ProcessEvents(SDL_Event& event);

void Update(float deltaTime);

void Render();

int main() {
	
	renderer.frameRender = Render;
	renderer.frameUpdate = Update;
	renderer.keyEvent = ProcessEvents;
	renderer.setWindowSize(window_size);
	renderer.init();
	renderer.setMouseCursorVisible(false);
	camera.setWindowCoordinates();
	atlas = sre::SpriteAtlas::create("data/snake.json",
		"data/snake.png");

	//sprite = atlas->get("berry.png");
	//sprite.setPosition(glm::vec2(20, 20))

	if (atlas == nullptr) {
		std::cerr << "Error: SpriteAtlas is not initialized!" << std::endl;
		return 0;  // Avoid further processing if atlas is not initialized
	}
	InitGame();
	
	renderer.startEventLoop();

	return 0;
}

void InitGame() {
	engine.Init(window_size);

	score.Init();
	player.Init(atlas);
	collectible.Init(engine,atlas);
}

void ProcessEvents(SDL_Event& event) {
	engine.ProcessEvents(event);
	player.ProcessEvents(engine.input);
}

void Update(float deltaTime) {
	engine.Update();
	player.Update(engine.frame);
	std::cout << player.GetPosX() << " " << player.GetPosY() << "\n";
	std::cout << collectible.GetPosX() << " " << collectible.GetPosY() << "\n";
	std::cout << "----------------------------" << "\n";


	// check death
	if (player.IsOverlapping())
	{
		++score.deaths;
		score.score = 0;
		renderer.init();
		player.Init(atlas);
		collectible.Init(engine,atlas);
	}

	// check collection
	if (
		player.GetPosX() == collectible.GetPosX() &&
		player.GetPosY() == collectible.GetPosY()
		)
	{
		++score.score;
		player.Grow();
		collectible.Init(engine,atlas);
	}
}

void Render() {
	sre::RenderPass renderPass = sre::RenderPass::create()
		.withCamera(camera)
		.withClearColor(true, { .3f, .3f, 1, 1 })
		.build();
	sre::SpriteBatch::SpriteBatchBuilder spriteBatchBuilder
		= sre::SpriteBatch::create();
	// send spriteBatchBuilder to your game elements, so that they can add their sprites for rendering
		//spriteBatchBuilder.addSprite(sprite);
	
	collectible.Render(spriteBatchBuilder);
	player.Render(spriteBatchBuilder);

	auto spriteBatch = spriteBatchBuilder.build();
	renderPass.draw(spriteBatch);
}