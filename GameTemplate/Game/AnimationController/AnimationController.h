#pragma once
#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"

#include "IPlayerState.h"
#include "IdleAnimation.h"
//enum animNum {
//	animidle,
//	animwalk,
//	animrun,
//	animjump
//};
class AnimationController : public IGameObject

{
public:
	AnimationController();
	~AnimationController();
	bool Start();
	void Update();
	void SetModel(SkinModel& model)
	{
		m_model = &model;
	}

	const Animation& GetAnimation() const
	{
		return m_animation;
	}
	void SetAnimation(const Animation& anim)
	{
		m_animation = anim;
	}
private:
	void ChangeState(IPlayerState* nextState);
private:
	IPlayerState* m_currentState = nullptr;		//現在のステート。
	IdleAnimation m_idelAnimation;
	SkinModel* m_model;
	Animation m_animation;
	//AnimationClip m_animationCrip[4];
	AnimationClip m_animationCrip[1];
	bool m_isMove = false; //移動フラグ
	bool m_isrun = false; //走りフラグ
	bool m_isJump = false; //ジャンプフラグ
};