#pragma once
class IPlayerState
{
	public:
		virtual void Update() = 0;
		//ƒWƒƒƒ“ƒv‚Å‚«‚éH
		virtual bool IsPossibleJump() = 0;
		

};

