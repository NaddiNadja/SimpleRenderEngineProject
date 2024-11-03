#include "Player.h"

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"
#include "../Engine/MyEngine.h"



namespace Snake {
	sre::Sprite player_sprite;

	void Player::Grow() {
		pos_x.emplace_back(pos_x.back());
		pos_y.emplace_back(pos_y.back());
		sprites.emplace_back(sprites.back());
	}

	bool Player::IsOverlapping() {
		// We can never overlap with less than 4 elements, so we skip the computation.
		// This avoid an annoying special case where the last and second-to last elements briefly overlap
		// between `Grow()` and the first advance
		if (pos_x.size() < 4)
			return false;

		auto it_x = pos_x.begin();
		auto it_y = pos_y.begin();

		// the head will always overlap itself, so we skip it
		++it_x;
		++it_y;

		while (it_x != pos_x.end() && it_y != pos_y.end())
		{
			if (*it_x == GetPosX() && *it_y == GetPosY())
				return true;
			++it_x;
			++it_y;
		}

		return false;
	}

	void Player::Init(std::shared_ptr<sre::SpriteAtlas> atlas) {
		player_sprite = atlas->get("snake-body.png");
		pos_x.clear();
		pos_y.clear();

		pos_x.emplace_front(PLAYER_START_X);
		pos_y.emplace_front(PLAYER_START_Y);

		// we start the game moving towards the right
		dir_x = 1;
		dir_y = 0;

		sprites.emplace_front(player_sprite);
	}

	void Player::ProcessEvents(char input) {
		if (input == SDLK_w) { dir_x = 0; dir_y = 1; }
		if (input == SDLK_s) { dir_x = 0; dir_y = -1; }
		if (input == SDLK_a) { dir_x = -1; dir_y = 0; }
		if (input == SDLK_d) { dir_x = 1; dir_y = 0; }
		if (input == SDLK_2) {
			std::cout << "GROW" << "\n";
			std::cout << sprites.size() << "\n";
			Grow();
		}
	}

	void Player::Update(int frame) {
		animation_frame = (frame / 20) % 2;

		if (frame % PLAYER_SPEED == 0)
		{
			erase_x = pos_x.back();
			erase_y = pos_y.back();
			// `:` is syntax sugar for an getting the list iterator, andvancing it until the end,
			// and getting the value at each step
			int next_x = pos_x.front() + dir_x * 25;
			for (int& x : pos_x)
			{
				int curr_x = x;
				x = next_x;
				next_x = curr_x;
			}

			int next_y = pos_y.front() + dir_y * 25;
			for (int& y : pos_y)
			{
				int curr_y = y;
				y = next_y;
				next_y = curr_y;
			}
		}
	}

	void Player::Render(sre::SpriteBatch::SpriteBatchBuilder& SpriteBatchBuilder) {
		// here we need to iterate the two lists at the same time, so we run the iterators the verbose way
		auto it_x = pos_x.begin();
		auto it_y = pos_y.begin();
		auto it_sprite = sprites.begin();
		while (it_x != pos_x.end() && it_y != pos_y.end() && it_sprite != sprites.end())
		{
			// In this context, the `*` meaning is "give me the element at the position that this iterator reached.
			// We will understand properly what it does next week when we talk about pointers
			player_sprite.setPosition(glm::vec2(*it_x, *it_y));
			//ITUGames::Console::RenderCharacter(animation_frame ? '0' : 'O', *it_x, *it_y);
			SpriteBatchBuilder.addSprite(player_sprite);
			++it_x;
			++it_y;
		}
	}
}