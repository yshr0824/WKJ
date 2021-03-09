#pragma once

#include "IGameObject.h"
#include "util/Util.h"
#include "ShadowMap.h"

/// <summary>
/// �Q�[���I�u�W�F�N�g�̎��s�D��
/// </summary>
enum {
	enGameObjectPrio_MostHight,	//�ō��B
	enGameObjectPrio_High,		//�����B
	enGameObjectPrio_Middle,	//����
	enGameObjectPrio_Low,		//�Ⴂ�B
	enGameObjectPrio_MostLow,	//�Œ�B
};
class GameObjectManager
{
private:
	static unsigned int MakeGameObjectNameKey(const char* objectName)
	{
		static const unsigned int defaultNameKey = Util::MakeHash("Undefined");	//���O�L�[�B
		unsigned int hash;
		if (objectName == nullptr) {
			hash = defaultNameKey;
		}
		else {
			hash = Util::MakeHash(objectName);
		}
		return hash;
	}
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	GameObjectManager();
	/// <summary>
	/// ���s�B
	/// </summary>
	void Execute();
	//�������𖾎��I�ɌĂ�
	void Init();
	/// <summary>
	/// �Q�[���I�u�W�F�N�g��ǉ��B
	/// </summary>
	/// <param name="go"></param>
	void AddGameObject(IGameObject* go, const char* name)
	{
		m_gameObjects.push_back(go);
		go->SetName(name);
	}
	//New
	template<class T,class... TArgs>
	T* NewGameObject(GameObjectPrio prio, const char* objectName) 
	{
		T* newObject = new T();
		newObject->Awake();
		newObject->SetMarkNewFromGameObjectManager();
		m_gameObjectListArray.at(prio).push_back(newObject);
		unsigned int hash = MakeGameObjectNameKey(objectName);
		newObject->SetRegist(true);
		newObject->SetPriority(prio);
		newObject->SetNamekey(hash);
		return newObject;
	}
	//Deleto
	void DeleteGameObject(IGameObject* go);
	
	void RegistShadowCaster(SkinModel* shadowCaster)
	{
		m_shadowMap.RegistShadowCaster(shadowCaster);
	}
	ShadowMap* GetShadowMap()
	{
		return &m_shadowMap;
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g��j���B
	/// </summary>
	/// <param name="go"></param>
	
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�𖼑O�Ō����B
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	IGameObject* FindGameObject(const char* name)
	{
		for (int i = 0; i < m_gameObjects.size(); i++) {
			if (m_gameObjects[i]->EqualName(name)		//���O�������B
				&& m_gameObjects[i]->IsDead() == false //����ł��Ȃ��B
				) {
				//���������B
				return m_gameObjects[i];
			}
		}
		//������Ȃ��B
		return nullptr;
	}

	static GameObjectManager& Instance()
	{
		static GameObjectManager instance;
		instance.m_gameObjectListArray.resize(255);
		return instance;
	}

private:
	ShadowMap m_shadowMap;	//�V���h�E�}�b�v�B
	std::vector< IGameObject* > m_gameObjects;
	typedef std::list<IGameObject*>	GameObjectList; //GameObjectList��List<IGameObject>�̃|�C���g�^�ɂ���
	std::vector<GameObjectList > m_gameObjectListArray; //�Q�[���I�u�W�F�N�g�̃��X�g
	std::vector<IGameObject* > m_deleatObjectList; //�폜����I�u�W�F�N�g�̃��X�g
	
};


extern GameObjectManager g_goMgr;

static inline GameObjectManager& IGameObjectManager()
{
	return GameObjectManager::Instance();
}

template<class T>
static inline T* NewGO(int priority, const char* objectName = nullptr)
{
	return IGameObjectManager().NewGameObject<T>((GameObjectPrio)priority, objectName);
}

static inline void DeleteGO(IGameObject* go)
{
	IGameObjectManager().DeleteGameObject(go);
}