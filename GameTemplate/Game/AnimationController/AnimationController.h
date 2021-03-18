#pragma once
#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"

//#include "IPlayerState.h"
//#include "WalkAnimation.h"
enum animNum {
	animidle,
	animwalk,
	animrun,
	animjump
};
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
private:
	SkinModel* m_model;
	Animation m_animation;
	AnimationClip m_animationCrip[4];
	bool m_isMove = false; //移動フラグ
	bool m_isrun = false; //走りフラグ
	bool m_isJump = false; //ジャンプフラグ
//private:
//	template<class T> void ChangeState();
private:
	//IPlayerState* currentState;	//現在のステート。
};


