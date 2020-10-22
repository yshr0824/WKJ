#include "stdafx.h"
#include "GameObjectManager.h"
#include "IGameObject.h"

GameObjectManager g_goMgr;

void GameObjectManager::Execute()
{
	IGameObject* a =new IGameObject();
		//Start�֐����Ăяo���B
	for (int i = 0; i < m_gameObjectListArray.size(); i++) {
		GameObjectList& glist = m_gameObjectListArray[i];
		for (IGameObject* go : glist) {  
			if (go->IsStart() == false) {
				go->Start();
			//�X�^�[�g�ς݂̈������B
				go->MarkStarted();
			}
		}
	}
	//Update�֐����Ăяo���B
	for (int i = 0; i < m_gameObjectListArray.size(); i++) {
		GameObjectList& glist = m_gameObjectListArray[i];
		for(IGameObject*go : glist){
			if (go->IsStart() == true
				&& go->IsDead() == false
				) {
				//�J�n�ς݁A������ł��Ȃ��B
				go->Update();
			}
		}
	}
	//Draw�֐����Ăяo���B
	for (int i = 0; i < m_gameObjectListArray.size(); i++) {
		GameObjectList& glist = m_gameObjectListArray[i];
		for(IGameObject*go : glist){
			if (go->IsStart() == true	
				&& go->IsDead() == false
			) {
				//�J�n�ς݁A������ł��Ȃ��B
				go->Draw();
			}
		}
	}

	//����ł���z�������B
	std::vector< IGameObject* > tmp = m_deleatObjectList;
	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i]->IsDead()) {
			//���S���Ă���B
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