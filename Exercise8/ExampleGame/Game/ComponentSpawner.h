#pragma once

#include "Engine/Component.h"

class ComponentSpawner : public MyEngine::Component {
	void Init(rapidjson::Value&) override;

	void SpawnWall(std::string name, std::string sprite, glm::vec3 pos);
	void SpawnFloor(std::string name, std::string sprite, glm::vec3 pos);
	void SpawnCoin(std::string name, std::string sprite, glm::vec3 pos);
};