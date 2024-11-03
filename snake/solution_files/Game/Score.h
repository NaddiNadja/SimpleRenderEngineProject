#pragma once

#include "../Engine/Component.h"

namespace Snake {
	class Score : public MyEngine::Component {
	public:
		int score;
		int deaths;

		void Init();
		void Render();
	};
}