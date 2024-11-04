#include "ComponentSpawner.h"
#include "ComponentPickup.h"

#include "Engine/MyEngine.h"
#include "Engine/Components/ComponentRendererSprite.h"

#include "Engine/Components/ComponentPhysicsBody.h"

void ComponentSpawner::Init(rapidjson::Value&) {
	float winHeight = MyEngine::Engine::GetInstance()->GetScreenSize().y;

	// these should probably go in the json file
	// you can tweak these to find a pipe distriv
	float xOffsetStart = 45;
	float curve = 250;
	float heighVariation = 10;
	float xVariation = 50;
	int nWalls = 50;
	
	for (int i = 0; i < nWalls; ++i) {
		float xOffset = xVariation * cos(i * curve * 0.2f) + xOffsetStart;
		glm::vec3 posBot {
			i * 300 + xOffset,
			sin(i * curve) * heighVariation,
			0
		};
		glm::vec3 posTop {
			i * 300 + xOffset,
			winHeight - posBot.y,
			0
		};
		glm::vec3 posCoin{
			i * 300 + xOffset,
			 (posTop.y + posBot.y) / 2 + (std::rand() % 100 + 20),
			//cos(i * curve) * (std::rand() % 60 + 20) + (posTop.y + posBot.y) / 2,
			0
		};

		SpawnWall("WallBottom" + std::to_string(i), "column_bottom.png", posBot);
		SpawnWall("WallTop" + std::to_string(i), "column_top.png", posTop);
		SpawnCoin("Coin" + std::to_string(i), "coin.png", posCoin);
	}

	// TODO spawn floor
	for (int i = 0; i < nWalls; i++) {
		SpawnFloor("Floor" + std::to_string(i), "background2", glm::vec3(i * 255, 0, 0));
	}

	// TODO spawn coins
}

void ComponentSpawner::SpawnWall(std::string name, std::string spriteId, glm::vec3 pos) {
	auto engine = MyEngine::Engine::GetInstance();
	auto gameObject = GetGameObject();

	auto wall = engine->CreateGameObject(name, gameObject).lock();
	auto renderer = wall->CreateComponent<ComponentRendererSprite>().lock();
	renderer->SetSprite("bird", spriteId);

	auto sprite = renderer->GetSprite();
	sprite->setScale({ 2, 2 });

	pos.y += sprite->getSpriteSize().y / 2;
	std::cout << pos.y << " " << name << " pos y" << std::endl;
	wall->SetPosition(pos);

	// TODO add body
	auto body = wall->CreateComponent<ComponentPhysicsBody>().lock();

	glm::vec2 s { sprite->getSpriteSize().x, sprite->getSpriteSize().y};
	body->CreateBody(b2_staticBody, false, s);
}

void ComponentSpawner::SpawnFloor(std::string name, std::string spriteId, glm::vec3 pos) {
	auto engine = MyEngine::Engine::GetInstance();
	auto gameObject = GetGameObject();

	auto floor = engine->CreateGameObject(name, gameObject).lock();
	auto renderer = floor->CreateComponent<ComponentRendererSprite>().lock();
	renderer->SetSprite("SINGLE", spriteId);

	auto sprite = renderer->GetSprite();
	sprite->setScale({ 2, 2 });

	pos.y += sprite->getSpriteSize().y / 2 - 109;
	floor->SetPosition(pos);

	// TODO add body
	auto body = floor->CreateComponent<ComponentPhysicsBody>().lock();

	glm::vec2 s{ sprite->getSpriteSize().x, 112 };
	body->CreateBody(b2_staticBody, false, s);
}

void ComponentSpawner::SpawnCoin(std::string name, std::string spriteId, glm::vec3 pos) {
	auto engine = MyEngine::Engine::GetInstance();
	auto gameObject = GetGameObject();

	auto coin = engine->CreateGameObject(name, gameObject).lock();
	auto renderer = coin->CreateComponent<ComponentRendererSprite>().lock();
	renderer->SetSprite("bird", spriteId);

	auto sprite = renderer->GetSprite();
	sprite->setScale({ 2, 2 });

	pos.y += sprite->getSpriteSize().y / 2;
	std::cout << pos.y << " coin pos y" << std::endl;
	coin->SetPosition(pos);

	auto body = coin->CreateComponent<ComponentPhysicsBody>().lock();

	glm::vec2 s{ sprite->getSpriteSize().x, sprite->getSpriteSize().y };
	body->CreateBody(b2_staticBody, true, s);
}