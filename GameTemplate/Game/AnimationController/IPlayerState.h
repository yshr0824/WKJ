#pragma once
class IPlayerState
{
	public:
		virtual void Update() = 0;
		//ジャンプできる？
		virtual bool IsPossibleJump() = 0;
		

};

