#include "Collectible.h"

#include <random>

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"
#include "../Engine/MyEngine.h"


namespace Snake {
	sre::Sprite berry_sprite;
	void Collectible::Init(MyEngine::Engine& engine, std::shared_ptr<sre::SpriteAtlas> atlas) {
        const int GRID_SIZE = 25;
		/*int min_x = PLAY_AREA_MARGINS * 25;
		int min_y = PLAY_AREA_MARGINS * 25;
		int max_x = engine.GetScreenWidth()  - PLAY_AREA_MARGINS * 25;
		int max_y = engine.GetScreenHeight() - PLAY_AREA_MARGINS * 25;*/

		/*pos_x = std::rand() * 25 % (max_x - min_x) + min_x;
		pos_y = std::rand() * 25 % (max_y - min_y) + min_y;*/


        int min_x = PLAY_AREA_MARGINS * GRID_SIZE;
        int min_y = PLAY_AREA_MARGINS * GRID_SIZE;
        int max_x = ((engine.GetScreenWidth() - PLAY_AREA_MARGINS * GRID_SIZE) / GRID_SIZE) * GRID_SIZE;
        int max_y = ((engine.GetScreenHeight() - PLAY_AREA_MARGINS * GRID_SIZE) / GRID_SIZE) * GRID_SIZE;

        // Make sure we have valid ranges
        if (max_x <= min_x) max_x = min_x + GRID_SIZE;
        if (max_y <= min_y) max_y = min_y + GRID_SIZE;

        // Calculate number of possible grid positions
        int num_cells_x = (max_x - min_x) / GRID_SIZE + 1;
        int num_cells_y = (max_y - min_y) / GRID_SIZE + 1;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis_x(0, num_cells_x - 1);
        std::uniform_int_distribution<> dis_y(0, num_cells_y - 1);

        // Convert grid cell index back to pixels
        pos_x = min_x + (dis_x(gen) * GRID_SIZE);
        pos_y = min_y + (dis_y(gen) * GRID_SIZE);

		berry_sprite = atlas->get("berry.png");
		berry_sprite.setPosition(glm::vec2(pos_x, pos_y));

	}

	void Collectible::Update() { }

	void Collectible::Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder) {
		spriteBatchBuilder.addSprite(berry_sprite);
	}
}