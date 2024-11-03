#include "GameObject.h"

namespace MyEngine {
	void GameObject::Init() {
		for (auto& component : _components)
			component.Init();

		for (auto& child : _children)
			child.Init();
	}

	void GameObject::Update() {
		for (auto& component : _components)
			component.Update();

		for (auto& child : _children)
			child.Update();
	}
}