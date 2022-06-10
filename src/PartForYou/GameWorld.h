#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#include <list>
#include "WorldBase.h"
#include "GameObjects.h"

class GameWorld : public WorldBase {
public:
  GameWorld();
  virtual ~GameWorld();

  virtual void Init() override;

  virtual LevelStatus Update() override;

  virtual void CleanUp() override;

  virtual bool IsGameOver() const override;

  int Detect(GameObject* obj, int type);

  Dawnbreaker* GetDawnbreaker() const;

  void AddIn(GameObject* obj);

  void IncreasDestroyed(int n);

private:
	int lives;
	int destoryed = 0;
	int onScreen = 0;
	int allowed;
	Dawnbreaker* dawnbreaker;
	std::list<GameObject*> ObjectList;
};

#endif // !GAMEWORLD_H__
