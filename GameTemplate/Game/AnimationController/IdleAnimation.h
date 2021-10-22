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
	//ジャンプできる？
	virtual bool IsPossibleJump()
	{
		//飛べる。
		return true;
	}
	void SetIdelModel(SkinModel& model)
	{
		m_model = &model;
	}
private:
	//AnimationController* m_animcontroller = nullptr;

	SkinModel* m_model; //AnimationControllerのm_modelをもらう。
	Animation m_idleanimation;
	AnimationClip m_animationCrip[1];
};

