#pragma once
#include "IPlayerState.h"
#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
class WalkAnimation : public IPlayerState
{
public:
	WalkAnimation();
	~WalkAnimation();
	bool Start();
	virtual void Update();
	//�W�����v�ł���H
	virtual bool IsPossibleJump()
	{
		//��ׂȂ��B
		return true;
	}
private:

	Animation m_animation;
	AnimationClip m_animationCrip;
};

