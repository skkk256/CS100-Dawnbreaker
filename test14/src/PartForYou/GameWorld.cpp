#include "GameWorld.h"
#include "GameObjects.h"
#include "Enemy.h"
#include "utils.h"
#include "Meteors.h"
#include "Star.h"
#include "Projectile.h"
#include <algorithm>
#include <sstream>


GameWorld::GameWorld() : lives(3), dawnbreaker(nullptr), allowed(0), destoryed(0), onScreen(0){}

GameWorld::~GameWorld() {
	if (dawnbreaker != nullptr)
		CleanUp();
}

void GameWorld::Init() {
	destoryed = 0;
	onScreen = 0;
	dawnbreaker = new Dawnbreaker(300, 100, this);
	for (int i = 0; i < 30; ++i) {
		ObjectList.push_back(new Star(randInt(0, WINDOW_WIDTH - 1), randInt(0, WINDOW_HEIGHT - 1), randInt(10, 40) / 100.0));
	}
}

LevelStatus GameWorld::Update() {
	// ���ɱ����͵л����޸�bar
	std::stringstream bar;
	bar << "HP: " << dawnbreaker->GetHP() << "/100   "
		<< "Meteors: " << dawnbreaker->GetMeteors() << "   "
		<< "Lives: " << lives << "   "
		<< "Level: " << GetLevel() << "   "
		<< "Enemies: " << destoryed << "/" << 3 * GetLevel() << "   "
		<< "Score: " << GetScore() << "  ";
	SetStatusBarMessage(bar.str());

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
		int probability = randInt(1, temp);
		if (probability <= p1) {
			ObjectList.push_back(
				new Alphatron(randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT-1, 20 + 2 * GetLevel(), 4 + GetLevel(), 2 + GetLevel() / 5, this)
			);
			onScreen += 1;
		}
		else if ( probability > p1 && probability <= p2 + p1) {
			ObjectList.push_back(
				new Sigmatron(randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT-1, 25 + 5 * GetLevel(), 2 + GetLevel() / 5, this)
			);
			onScreen += 1;
		}
		else if (probability > p1 + p2 && probability <= p2 + p1 + p3) {
			ObjectList.push_back(
				new Omegatron(randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT-1, 20 + GetLevel(), 2 + 2 * GetLevel(), 3 + GetLevel() / 4, this)
			);
			onScreen += 1;
		}
	}
	//�������ж����dawnbreaker
	dawnbreaker->Update();
	int temp = dawnbreaker->NeedShoot();
	if ( temp == 1) {
		ObjectList.push_back(
			new Projectile(IMGID_BLUE_BULLET, dawnbreaker->GetX(), dawnbreaker->GetY() + 50, 0, 0.5 + 0.1 * dawnbreaker->GetUpgrade(), 5 + 3 * dawnbreaker->GetUpgrade(), false, this)
		);
	}
	else if (temp == 2) {
		ObjectList.push_back(
			new Meteors(dawnbreaker->GetX(), dawnbreaker->GetY() + 100, this)
		);
	}

	for (auto iter = ObjectList.begin(); iter != ObjectList.end(); iter++) {
		(*iter)->Update();
		switch ((*iter)->GetType())
		{
		case GameObject::alpha:
			if (((Enemy*)(*iter))->NeedShoot()) {
				ObjectList.push_front(
					new Projectile(IMGID_RED_BULLET, (*iter)->GetX(), (*iter)->GetY() - 50, 180, 0.5, ((Enemy*)(*iter))->GetAgreesivity(), true, this)
				);
				((Projectile*)(*ObjectList.begin()))->SetFlightStrategy(2);
			}
			break;
		case GameObject::sigma:
			break;
		case GameObject::omega:
			if (((Enemy*)(*iter))->NeedShoot()) {
				ObjectList.push_front(
					new Projectile(IMGID_RED_BULLET, (*iter)->GetX(), (*iter)->GetY() - 50, 162, 0.5, ((Enemy*)(*iter))->GetAgreesivity(), true, this)
				);
				((Projectile*)(*ObjectList.begin()))->SetFlightStrategy(3);
				ObjectList.push_front(
					new Projectile(IMGID_RED_BULLET, (*iter)->GetX(), (*iter)->GetY() - 50, 198, 0.5, ((Enemy*)(*iter))->GetAgreesivity(), true, this)
				);
				((Projectile*)(*ObjectList.begin()))->SetFlightStrategy(1);
			}
			break;
		}
	}
	//�ж���Ϸ�Ƿ����
	if (dawnbreaker->JudgeDestroyed()) {
		lives -= 1;
		return LevelStatus::DAWNBREAKER_DESTROYED;
	}
	if (destoryed == 3 * GetLevel()) {
		return LevelStatus::LEVEL_CLEARED;
	}
	//���Ӻ�ɾ������
	for (auto iter = ObjectList.begin(); iter != ObjectList.end();) {
		if ((*iter)->JudgeDestroyed()) {
			if ((*iter)->GetType() == GameObject::alpha || (*iter)->GetType() == GameObject::sigma || (*iter)->GetType() == GameObject::omega) {
				onScreen--;
			}
			delete* iter;
			ObjectList.erase(iter++);
		}
		else {
			++iter;
		}
	}
	return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
	delete dawnbreaker;
	dawnbreaker = nullptr;
	for (auto iter = ObjectList.begin(); iter != ObjectList.end();iter++) {
		delete *iter;
	}
	ObjectList.clear();
}


bool GameWorld::IsGameOver() const {
	if (lives == 0) { return true; }
	return false;
}

bool GameWorld::DetectPlayer(GameObject* obj, int type)
{
	int d = std::sqrt(pow(obj->GetX() - dawnbreaker->GetX(), 2) + pow(obj->GetY() - dawnbreaker->GetY(), 2));
	if (d < 30.0 * (obj->GetSize() + dawnbreaker->GetSize())) {
		obj->DestroyIt();
		if (type == GameObject::tool) {
			return true;
		}
		else if (type == GameObject::enemy) {
			IncreasDestroyed(1);
			ObjectList.push_back(new Explosion(obj->GetX(), obj->GetY()));
			dawnbreaker->SetHP(dawnbreaker->GetHP() - 20);
			if (dawnbreaker->GetHP() <= 0) {
				dawnbreaker->DestroyIt();
			}
			return true;
		}
		else if (type == GameObject::rproj) {
			dawnbreaker->SetHP(dawnbreaker->GetHP() - ((Projectile*)(obj))->GetHurt());
			if (dawnbreaker->GetHP() <= 0) {
				dawnbreaker->DestroyIt();
			}
			return true;
		}
	}
	return false;
}

int GameWorld::DetectHurt(GameObject* enemy) {
	for (auto ptr : ObjectList) {
		if ((ptr->GetType() == GameObject::proj || ptr->GetType() == GameObject::Meter)&& (!(ptr->IsEnemy())) && (!(ptr->JudgeDestroyed()))) {
			int d = std::sqrt(pow(enemy->GetX() - ptr->GetX(), 2) + pow(enemy->GetY() - ptr->GetY(), 2));
			if (d < 30.0 * (enemy->GetSize() + ptr->GetSize())) {
				switch (ptr->GetType()) {
				case GameObject::Meter:
					return 999;
				case GameObject::proj:
					ptr->DestroyIt();
 					return ((Projectile*)(ptr))->GetHurt();
				}
			}
		}
	}
	return 0;
}

bool GameWorld::DetectEnemy(GameObject* obj, int who) {
	bool flag = false;
	for (auto ptr : ObjectList) {
		int type = ptr->GetType();
		if ((type == GameObject::alpha || type == GameObject::sigma || type == GameObject::omega) && (!(ptr->JudgeDestroyed()))) {
			int d = std::sqrt(pow(obj->GetX() - ptr->GetX(), 2) + pow(obj->GetY() - ptr->GetY(), 2));
			if (d < 30.0 * (obj->GetSize() + ptr->GetSize())) {
				if (who == GameObject::Meter) {
					flag = true;
				}
				else if (who == GameObject::bproj) {
					obj->DestroyIt();
					((Enemy*)(ptr))->SetHP(((Enemy*)(ptr))->GetHP() - ((Projectile*)(obj))->GetHurt());
					if (((Enemy*)(ptr))->GetHP() <= 0) {
						flag = true;
					}
					else {
						return true;
					}
				}
				if (flag) {
					IncreasDestroyed(1);
					ptr->DestroyIt();
					ObjectList.push_back(new Explosion(ptr->GetX(), ptr->GetY()));
					switch (((Enemy*)(ptr))->GetType())
					{
					case GameObject::alpha:
						IncreaseScore(50);
						return true;
					case GameObject::sigma:
						IncreaseScore(100);
						return true;
					case GameObject::omega:
						IncreaseScore(200);
						return true;
					}
				}
			}

		}
	}
	return false;
}


Dawnbreaker* GameWorld::GetDawnbreaker() const
{
	return dawnbreaker;
}

void GameWorld::AddIn(GameObject* obj)
{
	ObjectList.push_front(obj);
}

void GameWorld::IncreasDestroyed(int n)
{
	destoryed += n;
}


