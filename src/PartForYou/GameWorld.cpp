#include "GameWorld.h"
#include "GameObjects.h"
#include "utils.h"

GameWorld::GameWorld() : life(3), dawnbreaker(nullptr) {
}

GameWorld::~GameWorld() {

}

void GameWorld::Init() {
	dawnbreaker = new Dawnbreaker(300, 100, this);
	for (int i = 1; i < 30; ++i) {
		ObjectList.push_back(new Star(randInt(0, WINDOW_WIDTH - 1), randInt(0, WINDOW_HEIGHT - 1), randInt(10, 40) / 100.0));
	}
}

LevelStatus GameWorld::Update() {
	if (randInt(1, 30) == 1)
		ObjectList.push_back(new Star(randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT, randInt(10, 40) / 100.0));
	dawnbreaker->Update();
	for (auto iter = ObjectList.begin(); iter != ObjectList.end(); iter++) {
		(*iter)->Update();
	}
	if (IsGameOver()) {
		life -= 1;
		return LevelStatus::DAWNBREAKER_DESTROYED;
	}

	for (auto iter = ObjectList.begin(); iter != ObjectList.end(); iter++) {
		if ((*iter)->JudgeDestroyed()) {
			ObjectList.remove(*iter);
		}
	}
}

void GameWorld::CleanUp() {

}


bool GameWorld::IsGameOver() const {
  return false;
}
