#include "stdafx.h"
#include "system/system.h"
#include "Player/Player.h"
#include "Game.h"
#include "level/Level.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	NewGO<Game>(enGameObjectPrio_Middle,"game");
	
	IGameObjectManager().Init();
	
	//プレイヤー
	//Player player;
    
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		
		//物理エンジンの更新。
		g_physics.Update();
		//プレイヤーの更新。
		//player.Update();
		//プレイヤーの描画。
		//player.Draw();
		IGameObjectManager().Execute();
		//カメラの更新。
		//g_camera3D.Update();
		//描画終了。

		g_graphicsEngine->EndRender();
	}
}