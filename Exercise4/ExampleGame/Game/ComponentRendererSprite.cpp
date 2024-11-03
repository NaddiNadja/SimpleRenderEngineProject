#include "ComponentRendererSprite.h"
#include "Engine/MyEngine.h"

namespace ExampleGame {
	void ComponentRendererSprite::Render(sre::SpriteBatch::SpriteBatchBuilder& builder) {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();

		glm::vec2 screensize = engine->GetScreenSize();

		sprite.setRotation(parent->rotation);
		sprite.setPosition(parent->position);
		builder.addSprite(sprite);

		if (parent->wraps) {
			sprite.setPosition(glm::vec2(parent->position.x, parent->position.y - screensize.y));
			builder.addSprite(sprite);
		
			sprite.setPosition(glm::vec2(parent->position.x, parent->position.y + screensize.y));
			builder.addSprite(sprite);

			sprite.setPosition(glm::vec2(parent->position.x + screensize.x, parent->position.y));
			builder.addSprite(sprite);
		
			sprite.setPosition(glm::vec2(parent->position.x - screensize.x, parent->position.y));
			builder.addSprite(sprite);
		}
	}
}