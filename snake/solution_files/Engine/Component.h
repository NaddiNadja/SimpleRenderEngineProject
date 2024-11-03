#pragma once

#include "MyEngine.h"

namespace MyEngine {
	class Component {
	public:
		virtual void Init() {};
		virtual void Update() {};
	};
}