#include "stdafx.h"
#include "GameObjectManager.h"
#include "IGameObject.h"

GameObjectManager g_goMgr;

GameObjectManager::GameObjectManager()
{

}

void GameObjectManager::Init()
{
	m_shadowMap.Init();
}
void GameObjectManager::Execute()
{
	IGameObject* a =new IGameObject();
		//Start関数を呼び出す。
	for (int i = 0; i < m_gameObjectListArray.size(); i++) {
		GameObjectList& glist = m_gameObjectListArray[i];
		for (IGameObject* go : glist) {  
			if (go->IsStart() == false) {
				go->Start();
			//スタート済みの印をつける。
				go->MarkStarted();
			}
		}
	}

	//Update関数を呼び出す。
	for (int i = 0; i < m_gameObjectListArray.size(); i++) {
		GameObjectList& glist = m_gameObjectListArray[i];
		for(IGameObject*go : glist){
			if (go->IsStart() == true
				&& go->IsDead() == false
				) {
				//開始済み、かつ死んでいない。
				go->Update();
			}
		}
	}
	//シャドウマップにカメラから見た深度値を書き込んでいく
	//①シャドウマップ書き込み用のレンダリングターゲットを設定する。
	//②深度値を書き込みたいモデルを描画していく
	//		->使用するシェーダーはシャドウマップ書き込み用のシェーダーを使用する。
	

	//ライトビュー行列とライトプロジェクション行列を更新する。
	
	m_shadowMap.Update({ 1000.0f,1000.1000f,0.0f }, {0.0f,0.0f,0.0f});
	
	///////////////////////////////////////////////
	//シャドウマップにレンダリング
	///////////////////////////////////////////////
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//現在のレンダリングターゲットをバックアップしておく。
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	d3dDeviceContext->OMGetRenderTargets(
		1,
		&oldRenderTargetView,
		&oldDepthStencilView
	);
	//ビューポートもバックアップを取っておく。
	unsigned int numViewport = 1;
	D3D11_VIEWPORT oldViewports;
	d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);

	//シャドウマップにライトから見た深度値を書き込む。
	m_shadowMap.RenderToShadowMap();

	//元に戻す。
	d3dDeviceContext->OMSetRenderTargets(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);
	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
	//レンダリングターゲットとデプスステンシルの参照カウンタを下す。
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();
	


	//レンダリングターゲットをもとに戻す。

	//Draw関数を呼び出す。
	for (int i = 0; i < m_gameObjectListArray.size(); i++) {
		GameObjectList& glist = m_gameObjectListArray[i];
		for(IGameObject*go : glist){
			if (go->IsStart() == true	
				&& go->IsDead() == false
			) {
				//開始済み、かつ死んでいない。
				go->Draw();
			}
		}
	}

	//死んでいる奴を除去。
	std::vector< IGameObject* > tmp = m_deleatObjectList;
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->IsDead()) {
			//死亡している。
			auto gameObjectList = m_gameObjectListArray.at(tmp[i]->GetPriority());
			auto it = std::find(gameObjectList.begin(), gameObjectList.end(), tmp[i] );
			
			delete *it;
			gameObjectList.erase(it);
		}
	}
	m_deleatObjectList.clear();
}




void GameObjectManager::DeleteGameObject(IGameObject* go)
{
	if (go != nullptr
		&& go->GetRegist()
		) {
		go->SetMarkDead();
		//go->OnDestroyWrapper();
		go->SetRegist(false);
		go->SetRegistDeadList(true);
		m_deleatObjectList.push_back(go);
		go = nullptr;
	}
}