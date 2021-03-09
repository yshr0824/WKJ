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
	//�V���h�E�}�b�v�ɃJ�������猩���[�x�l����������ł���
	//�@�V���h�E�}�b�v�������ݗp�̃����_�����O�^�[�Q�b�g��ݒ肷��B
	//�A�[�x�l���������݂������f����`�悵�Ă���
	//		->�g�p����V�F�[�_�[�̓V���h�E�}�b�v�������ݗp�̃V�F�[�_�[���g�p����B
	

	//���C�g�r���[�s��ƃ��C�g�v���W�F�N�V�����s����X�V����B
	
	m_shadowMap.Update({ 1000.0f,1000.1000f,0.0f }, {0.0f,0.0f,0.0f});
	
	///////////////////////////////////////////////
	//�V���h�E�}�b�v�Ƀ����_�����O
	///////////////////////////////////////////////
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//���݂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v���Ă����B
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	d3dDeviceContext->OMGetRenderTargets(
		1,
		&oldRenderTargetView,
		&oldDepthStencilView
	);
	//�r���[�|�[�g���o�b�N�A�b�v������Ă����B
	unsigned int numViewport = 1;
	D3D11_VIEWPORT oldViewports;
	d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);

	//�V���h�E�}�b�v�Ƀ��C�g���猩���[�x�l���������ށB
	m_shadowMap.RenderToShadowMap();

	//���ɖ߂��B
	d3dDeviceContext->OMSetRenderTargets(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);
	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
	//�����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̎Q�ƃJ�E���^�������B
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();
	


	//�����_�����O�^�[�Q�b�g�����Ƃɖ߂��B

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