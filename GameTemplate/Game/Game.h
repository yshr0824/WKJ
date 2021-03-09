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
	
	////Effekseer�̏�����
	//void InitEffekseer();

	Player* m_player = nullptr;
	Stage* m_stage = nullptr;
	GameCamera* m_gamecamera = nullptr;
private:
	//Effekseer�}�l�[�W���Ǘ��B
	//81�s�ځ`85�s�ڂ܂ł̃����o���G�t�F�N�g���o�����߂�
	//�ǉ����������o�ϐ��B
	Effekseer::Manager* m_effekseerManager = nullptr;				//�Q�[�����ɃC���X�^���X�͈�������B
	EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;	//�Q�[�����ɃC���X�^���X�͈�������B
	Effekseer::Effect* m_sampleEffect = nullptr;					//�G�t�F�N�g��ɑ΂��ăC���X�^���X�͈���B
	Effekseer::Handle m_playEffectHandle = -1;						//�G�t�F�N�g��ɑ΂��ăC���X�^���X�͈���B
};

