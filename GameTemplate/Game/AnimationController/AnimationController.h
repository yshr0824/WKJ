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
	bool m_isMove = false; //�ړ��t���O
	bool m_isrun = false; //����t���O
	bool m_isJump = false; //�W�����v�t���O
//private:
//	template<class T> void ChangeState();
private:
	//IPlayerState* currentState;	//���݂̃X�e�[�g�B
};


