#pragma once

#include "sre/SpriteAtlas.hpp"
#include "../Engine/Component.h"

namespace Snake {
	class Collectible : public MyEngine::Component {
		const int PLAY_AREA_MARGINS = 4;

		int pos_x;
		int pos_y;
		sre::Sprite berry_sprite;

	public:
		inline int GetPosX() { return pos_x; }
		inline int GetPosY() { return pos_y; }

		void Init(MyEngine::Engine& engine, std::shared_ptr<sre::SpriteAtlas> atlas);
		void Update();
		void Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);
	};
}
