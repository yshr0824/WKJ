#pragma once
#include "IPlayerState.h"

class IdleAnimation : public IPlayerState
{
public:
	IdleAnimation();
	~IdleAnimation();
	virtual void Enter();
	virtual void Leave();
	virtual bool Start();
	virtual void Update();
	//�W�����v�ł���H
	virtual bool IsPossibleJump()
	{
		//��ׂ�B
		return true;
	}
	void SetIdelModel(SkinModel& model)
	{
		m_model = &model;
	}
private:
	//AnimationController* m_animcontroller = nullptr;

	SkinModel* m_model; //AnimationController��m_model�����炤�B
	Animation m_idleanimation;
	AnimationClip m_animationCrip[1];
};

