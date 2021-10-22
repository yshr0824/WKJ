#pragma once
class IPlayerState : public IGameObject
{
public:
	virtual void Enter() = 0;
	virtual void Leave() = 0;
	virtual bool Start() = 0;
	virtual void Update() = 0;
	//�W�����v�ł���H
	virtual bool IsPossibleJump() = 0;


private:
	SkinModel* m_model;
};
