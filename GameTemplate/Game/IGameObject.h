#pragma once
typedef unsigned char	GameObjectPrio;

class IGameObject
{
public:
	virtual ~IGameObject()
	{
	}
	virtual void Update() {};  //�A�b�v�f�[�g
	virtual void Draw() {};  //�h���[
	virtual bool Start() { return true; };

	virtual void OnDestroy() {}  //�폜�����Ƃ��ɌĂ΂��

	//�C�x���g
	enum EnEvent {
		enEvent_Undef,			//!<����`�C�x���g�B
		enEvent_Destroy,		//!<�C���X�^���X���j�������B
		enBaseClassEvent_Num,	//!<���N���X�Œ�`����Ă���C�x���g�̐��B
		enEvent_User,			//!<����ȍ~�Ƀ��[�U�[��`�̃C�x���g���쐬���Ă��������B

	};
	
	//�C�x���g�������̃f�[�^�B
	
	struct SEventParam {
		EnEvent eEvent = enEvent_Undef;			//!<�������Ă���C�x���g�B
		IGameObject* gameObject = nullptr;		//!<�C�x���g��ʒm���Ă���Q�[���I�u�W�F�N�g�̃C���X�^���X�B
	};

	/// <summary>
	/// �J�n���Ă��邩����B
	/// </summary>
	/// <returns></returns>
	bool IsStart() const
	{
		return m_isStart;
	}
	/// <summary>
	/// ���S���Ă��邩����B
	/// </summary>
	/// <returns></returns>
	bool IsDead() const
	{
		return m_isDead;
	}
	/// <summary>
	/// �J�n�ς݂̃t���O�𗧂Ă�B
	/// </summary>
	void MarkStarted()
	{
		m_isStart = true;
	}
	/// <summary>
	/// ���S�t���O�𗧂Ă�B
	/// </summary>
	void SetMarkDead()  
	{
		m_isDead = true;
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̖��O��ݒ肷��B
	/// </summary>
	/// <param name="name"></param>
	void SetName(const char* name)
	{
		if (name != nullptr) {
			//���O���w�肳��Ă���B
			m_name = name;
		}
	}
	/// <summary>
	/// ���O��������������B
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
		//�f�X�g���C�C�x���g�����X�i�[�ɒʒm����B
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
	
	GameObjectPrio	m_priority;			//!<���s�D��x�B
	bool m_isStart = false;	//�J�n���Ă���H
	bool m_isDead = false;	//����ł�H
	bool m_isRegistDeadList = false;  //���S���X�g�ɂ܂�Ă���
	bool m_isNewFromGameObjectManager;	//!<GameObjectManager��new���ꂽ�B
	bool m_isRegist = false; //GameObjectMnager�ɓo�^����Ă���H
	unsigned int m_nameKey = 0; //���O�L�[
	std::string m_name;		//���O�B
	std::list<std::function<void(SEventParam& eventParam)>>	m_eventListeners;	//�C�x���g���X�i�[�B�B
};

