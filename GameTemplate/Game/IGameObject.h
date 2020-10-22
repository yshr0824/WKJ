#pragma once
typedef unsigned char	GameObjectPrio;

class IGameObject
{
public:
	virtual ~IGameObject()
	{
	}
	virtual void Update() {};  //アップデート
	virtual void Draw() {};  //ドロー
	virtual bool Start() { return true; };

	virtual void OnDestroy() {}  //削除されるときに呼ばれる

	//イベント
	enum EnEvent {
		enEvent_Undef,			//!<未定義イベント。
		enEvent_Destroy,		//!<インスタンスが破棄される。
		enBaseClassEvent_Num,	//!<基底クラスで定義されているイベントの数。
		enEvent_User,			//!<これ以降にユーザー定義のイベントを作成してください。

	};
	
	//イベント発生時のデータ。
	
	struct SEventParam {
		EnEvent eEvent = enEvent_Undef;			//!<発生しているイベント。
		IGameObject* gameObject = nullptr;		//!<イベントを通知しているゲームオブジェクトのインスタンス。
	};

	/// <summary>
	/// 開始しているか判定。
	/// </summary>
	/// <returns></returns>
	bool IsStart() const
	{
		return m_isStart;
	}
	/// <summary>
	/// 死亡しているか判定。
	/// </summary>
	/// <returns></returns>
	bool IsDead() const
	{
		return m_isDead;
	}
	/// <summary>
	/// 開始済みのフラグを立てる。
	/// </summary>
	void MarkStarted()
	{
		m_isStart = true;
	}
	/// <summary>
	/// 死亡フラグを立てる。
	/// </summary>
	void SetMarkDead()  
	{
		m_isDead = true;
	}
	/// <summary>
	/// ゲームオブジェクトの名前を設定する。
	/// </summary>
	/// <param name="name"></param>
	void SetName(const char* name)
	{
		if (name != nullptr) {
			//名前が指定されている。
			m_name = name;
		}
	}
	/// <summary>
	/// 名前が等しいか判定。
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	bool EqualName(const char* name)
	{
		if (strcmp(m_name.c_str(), name) == 0) {
			return true;
		}
		return false;
	}

	void OnDestroyWrapper()
	{
		SEventParam param;
		param.eEvent = enEvent_Destroy;
		param.gameObject = this;
		//デストロイイベントをリスナーに通知する。
		for (auto& listener : m_eventListeners) {
			listener(param);
		}
		OnDestroy();

	}

	void SetPriority(bool prio)
	{
		m_priority = prio;
	}
	bool GetPriority()
	{
		return m_priority;
	}
	void SetRegist(bool reg)
	{
		m_isRegist = reg;
	}
	bool GetRegist()
	{
		return m_isRegist;
	}
	void SetNamekey(bool namekey)
	{
		m_nameKey = namekey;
	}
	bool GetNamekey()
	{
		return m_nameKey;
	}
	void SetRegistDeadList(bool rdl)
	{
		m_isRegistDeadList = rdl;
	}
	bool GetRegistDeadList()
	{
		return m_isRegistDeadList;
	}
	void SetMarkNewFromGameObjectManager()
	{
		m_isNewFromGameObjectManager = true;
	}
	bool IsNewFromGameObjectManager() const
	{
		return m_isNewFromGameObjectManager;
	}

	virtual void Awake() {}
private:
	
	GameObjectPrio	m_priority;			//!<実行優先度。
	bool m_isStart = false;	//開始している？
	bool m_isDead = false;	//死んでる？
	bool m_isRegistDeadList = false;  //死亡リストにつまれている
	bool m_isNewFromGameObjectManager;	//!<GameObjectManagerでnewされた。
	bool m_isRegist = false; //GameObjectMnagerに登録されている？
	unsigned int m_nameKey = 0; //名前キー
	std::string m_name;		//名前。
	std::list<std::function<void(SEventParam& eventParam)>>	m_eventListeners;	//イベントリスナー。。
};

