#include "GameWorld.h"
#include "GameObjects.h"
#include "Enemy.h"
#include "utils.h"

//≤‚ ‘”√
GameWorld::GameWorld() : life(3), dawnbreaker(nullptr), allowed(5) {
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
	if (allowed > 0) {
		ObjectList.push_back(
			new Alphatron(randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT, 20, 4, 2)
		);
		allowed -= 1;
	}
	dawnbreaker->Update();
	
	for (auto iter = ObjectList.begin(); iter != ObjectList.end(); iter++) {
		(*iter)->Update();
	}
	
	if (IsGameOver()) {
		life -= 1;
		return LevelStatus::DAWNBREAKER_DESTROYED;
	}

	if (dawnbreaker->NeedShoot() == 1) {
		ObjectList.push_back(
			new Projectile(dawnbreaker->GetX(), dawnbreaker->GetY() + 50, 0.5 + 0.1 * dawnbreaker->GetUpgrade(), 5 + 3 * dawnbreaker->GetUpgrade())
		);
	}
	for (auto iter = ObjectList.begin(); iter != ObjectList.end();) {
		if ((*iter)->JudgeDestroyed()) {
			delete* iter;
			ObjectList.erase(iter++);
		}
		else {
			++iter;
		}
	}
}

void GameWorld::CleanUp() {
	delete dawnbreaker;
	for (auto iter = ObjectList.begin(); iter != ObjectList.end();) {
		delete* iter;
		ObjectList.erase(iter++);
	}
	ObjectList.clear();
}


bool GameWorld::IsGameOver() const {
  return false;
}
