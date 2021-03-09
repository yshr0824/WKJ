#pragma once

#include "IGameObject.h"
#include "util/Util.h"
#include "ShadowMap.h"

/// <summary>
/// ゲームオブジェクトの実行優先
/// </summary>
enum {
	enGameObjectPrio_MostHight,	//最高。
	enGameObjectPrio_High,		//高い。
	enGameObjectPrio_Middle,	//中間
	enGameObjectPrio_Low,		//低い。
	enGameObjectPrio_MostLow,	//最低。
};
class GameObjectManager
{
private:
	static unsigned int MakeGameObjectNameKey(const char* objectName)
	{
		static const unsigned int defaultNameKey = Util::MakeHash("Undefined");	//名前キー。
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
	/// コンストラクタ。
	/// </summary>
	GameObjectManager();
	/// <summary>
	/// 実行。
	/// </summary>
	void Execute();
	//初期化を明示的に呼ぶ
	void Init();
	/// <summary>
	/// ゲームオブジェクトを追加。
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
	/// ゲームオブジェクトを破棄。
	/// </summary>
	/// <param name="go"></param>
	
	/// <summary>
	/// ゲームオブジェクトを名前で検索。
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	IGameObject* FindGameObject(const char* name)
	{
		for (int i = 0; i < m_gameObjects.size(); i++) {
			if (m_gameObjects[i]->EqualName(name)		//名前が同じ。
				&& m_gameObjects[i]->IsDead() == false //死んでいない。
				) {
				//見つかった。
				return m_gameObjects[i];
			}
		}
		//見つからない。
		return nullptr;
	}

	static GameObjectManager& Instance()
	{
		static GameObjectManager instance;
		instance.m_gameObjectListArray.resize(255);
		return instance;
	}

private:
	ShadowMap m_shadowMap;	//シャドウマップ。
	std::vector< IGameObject* > m_gameObjects;
	typedef std::list<IGameObject*>	GameObjectList; //GameObjectListをList<IGameObject>のポイント型にする
	std::vector<GameObjectList > m_gameObjectListArray; //ゲームオブジェクトのリスト
	std::vector<IGameObject* > m_deleatObjectList; //削除するオブジェクトのリスト
	
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