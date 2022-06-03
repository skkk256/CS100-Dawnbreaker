#include "GameWorld.h"
#include "GameObjects.h"
#include "Enemy.h"
#include "utils.h"
#include <algorithm>
#include "Projectile.h"

//测试用
GameWorld::GameWorld() : life(3), dawnbreaker(nullptr), allowed(0), destoryed(0), onScreen(0){}

GameWorld::~GameWorld() {

}

void GameWorld::Init() {
	destoryed = 0;
	onScreen = 0;
	dawnbreaker = new Dawnbreaker(300, 100, this);
	for (int i = 1; i < 30; ++i) {
		ObjectList.push_back(new Star(randInt(0, WINDOW_WIDTH - 1), randInt(0, WINDOW_HEIGHT - 1), randInt(10, 40) / 100.0));
	}
}

LevelStatus GameWorld::Update() {
	// 生成背景和敌机
	int todestroyed = 3 * GetLevel() - destoryed;
	int maxOnScreen = (5 + GetLevel()) / 2;
	allowed = std::min(todestroyed, maxOnScreen);
	if (randInt(1, 30) == 1)
		ObjectList.push_back(new Star(randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT, randInt(10, 40) / 100.0));
	if ((allowed > onScreen)&& (randInt(1,100) <= allowed - onScreen)) {
		int p1 = 6;
		int p2 = 2 * std::max(GetLevel() - 1, 0);
		int p3 = 3 * std::max(GetLevel() - 2, 0);
		int temp = p1 + p2 + p3;
		if (randInt(1, temp) <= p1) {
			ObjectList.push_back(
				new Alphatron(randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT, 20 + 2 * GetLevel(), 4 + GetLevel(), 2 + GetLevel() / 5, dawnbreaker)
			);
			onScreen += 1;
		}
		else if (p1 < randInt(1, temp) <= p2) {
			ObjectList.push_back(
				new Sigmatron(randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT, 25 + 5 * GetLevel(), 2 + GetLevel() / 5, dawnbreaker)
			);
			onScreen += 1;
		}
		else if (p2 < randInt(1, temp) <= p3) {
			ObjectList.push_back(
				new Omegatron(randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT, 20 + GetLevel(), 2 + 2 * GetLevel(), 3 + GetLevel() / 4, dawnbreaker)
			);
			onScreen += 1;
		}
	}
	//遍历现有对象和dawnbreaker
	dawnbreaker->Update();
	for (auto iter = ObjectList.begin(); iter != ObjectList.end(); iter++) {
		(*iter)->Update();
		switch ((*iter)->GetType())
		{
		case GameObject::alpha:
			if (((Enemy*)(*iter))->NeedShoot()) {
				ObjectList.push_front(
					new Projectile(IMGID_RED_BULLET, (*iter)->GetX(), (*iter)->GetY() - 50, 180, 0.5, ((Enemy*)(*iter))->GetAgreesivity(), false)
				);
				((Projectile*)(*ObjectList.begin()))->SetFlightStrategy(2);
			}
			break;
		case GameObject::sigma:
			break;
		case GameObject::omega:
			if (((Enemy*)(*iter))->NeedShoot()) {
				ObjectList.push_front(
					new Projectile(IMGID_RED_BULLET, (*iter)->GetX(), (*iter)->GetY() - 50, 162, 0.5, ((Enemy*)(*iter))->GetAgreesivity(), false)
				);
				((Projectile*)(*ObjectList.begin()))->SetFlightStrategy(3);
				ObjectList.push_front(
					new Projectile(IMGID_RED_BULLET, (*iter)->GetX(), (*iter)->GetY() - 50, 198, 0.5, ((Enemy*)(*iter))->GetAgreesivity(), false)
				);
				((Projectile*)(*ObjectList.begin()))->SetFlightStrategy(1);
			}
			break;
		}
	}
	//判断游戏是否结束
	if (IsGameOver()) {
		life -= 1;
		return LevelStatus::DAWNBREAKER_DESTROYED;
	}
	//添加和删除对象
	if (dawnbreaker->NeedShoot() == 1) {
		ObjectList.push_back(
			new Projectile(IMGID_BLUE_BULLET, dawnbreaker->GetX(), dawnbreaker->GetY() + 50, 0, 0.5 + 0.1 * dawnbreaker->GetUpgrade(), 5 + 3 * dawnbreaker->GetUpgrade(), false)
		);
	}
	for (auto iter = ObjectList.begin(); iter != ObjectList.end();) {
		if ((*iter)->JudgeDestroyed()) {
			if ((*iter)->GetType() == GameObject::alpha || (*iter)->GetType() == GameObject::sigma || (*iter)->GetType() == GameObject::omega) {
				onScreen -= 1;
			}
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
