#pragma once
class Player;
class Stage;
class GameCamera;

class Game :public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	Player* m_player = nullptr;
	Stage* m_stage = nullptr;
	GameCamera* m_gamecamera = nullptr;
};

