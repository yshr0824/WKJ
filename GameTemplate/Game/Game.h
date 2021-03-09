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
	
	////Effekseerの初期化
	//void InitEffekseer();

	Player* m_player = nullptr;
	Stage* m_stage = nullptr;
	GameCamera* m_gamecamera = nullptr;
private:
	//Effekseerマネージャ管理。
	//81行目～85行目までのメンバがエフェクトを出すために
	//追加したメンバ変数。
	Effekseer::Manager* m_effekseerManager = nullptr;				//ゲーム中にインスタンスは一つだけ作る。
	EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;	//ゲーム中にインスタンスは一つだけ作る。
	Effekseer::Effect* m_sampleEffect = nullptr;					//エフェクト一つに対してインスタンスは一つ作る。
	Effekseer::Handle m_playEffectHandle = -1;						//エフェクト一つに対してインスタンスは一つ作る。
};

