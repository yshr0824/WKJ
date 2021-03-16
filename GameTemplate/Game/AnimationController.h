#pragma once
#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
#include "IPlayerState.h"
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
	template<class T> void ChangeState();
	IPlayerState* currentState;	//現在のステート。

};


