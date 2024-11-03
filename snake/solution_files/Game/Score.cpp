#include "Score.h"


namespace Snake {
	void Score::Init() {
		score = deaths = 0;
	}

	void Score::Render() {
		std::cout << " Score  : " << score << std::endl;
		std::cout << " Deaths : " << deaths << std::endl;
	}
}