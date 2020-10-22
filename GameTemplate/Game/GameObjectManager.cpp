#include "stdafx.h"
#include "GameObjectManager.h"
#include "IGameObject.h"

GameObjectManager g_goMgr;

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