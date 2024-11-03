#pragma once

#include <list>

#include "Component.h"

namespace MyEngine {
	class GameObject {
	public:
		std::list<GameObject> _children;
		std::list<Component> _components;

		void Init();
		void Update();
	};
}