#pragma once
class IPlayerState
{
	public:
		virtual void Update() = 0;
		//�W�����v�ł���H
		virtual bool IsPossibleJump() = 0;
		

};

