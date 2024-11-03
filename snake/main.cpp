//#include <chrono>
//
//#include "solution_files/Game/Player.h"
//#include "solution_files/Game/Score.h"
//#include "solution_files/Game/Collectible.h"
//#include "solution_files/ITUGames.h"
//
//
//void InitGame();
//bool ProcessEvents();
//void Update();
//void Render();
//
//MyEngine::Engine engine;
//
//Snake::Score		score;
//Snake::Player		player;
//Snake::Collectible	collectible;
//
//int main() {
//	bool bQuit = false;
//	InitGame();
//
//	while (!bQuit) {
//		engine.time_start = std::chrono::steady_clock::now();
//
//		bQuit = ProcessEvents();
//		Update();
//		Render();
//
//		engine.time_end_computation = std::chrono::steady_clock::now();
//		engine.time_computation = engine.time_end_computation - engine.time_start;
//
//		ITUGames::Utils::PreciseSleep(engine.MAX_FRAME_TIME - engine.time_computation);
//
//		engine.time_end = std::chrono::steady_clock::now();
//		engine.time_elapsed = engine.time_end - engine.time_start;
//	}
//
//	return 0;
//}
//
//void InitGame() {
//	engine.Init();
//
//	score.Init();
//	player.Init();
//	collectible.Init(engine);
//}
//
//bool ProcessEvents() {
//	engine.ProcessEvents();
//
//	player.ProcessEvents(engine.input);
//
//	return false;
//}
//
//void Update() {
//	if (engine.input == ITUGames::Console::KEY_2)
//		player.Grow();
//
//	engine.Update();
//	player.Update(engine.frame);
//
//	// check death
//	if (player.IsOverlapping())
//	{
//		++score.deaths;
//		score.score = 0;
//		ITUGames::Console::ClearScreen();
//		player.Init();
//		collectible.Init(engine);
//	}
//
//	// check collection
//	if (
//		player.GetPosX() == collectible.GetPosX() &&
//		player.GetPosY() == collectible.GetPosY()
//		)
//	{
//		++score.score;
//		player.Grow();
//		collectible.Init(engine);
//	}
//}
//
//void Render() {
//	ITUGames::Console::GotoTop();
//
//	engine.Render();
//	player.Render();
//	collectible.Render();
//
//	if (!engine.b_show_debug_window)
//		score.Render();
//}