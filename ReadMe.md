# This is my pet game project for C++(component based game design) study.

# Main

전체 게임의 기본 구조는 Initialize, Run, Shutdown 의 3단 구조로 이루어 진다.

```c
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pScmdline, int iCmdshow)
{
	unique_ptr<CGame> spGame = make_unique<CGame>();
	assert(spGame != nullptr);
	if(spGame->Initialize(hInstance, pScmdline, iCmdshow))
	{
		spGame->Run();
	}
	spGame->Shutdown();
	spGame.reset();

	return 0;
}
```

# CGame

CGame 클래스는 다음과 같이 이루어져 있다.


```c
class CGame
{	
public:
	CGame();
	~CGame();

	bool Initialize(HINSTANCE hInstance, LPSTR pScmdline, int iCmdshow, LPCWSTR applicationName = L"Zenity");
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool InitializeWindow(LPSTR pScmdline, int iCmdShow, int& outScreenWidth, int& outScrennHeight);
	void ShutdownWindow();

	bool Frame();
	bool Update();
	void Draw();
};
```

## public

---

### bool Initialize(HINSTANCE hInstance, LPSTR pScmdline, int iCmdshow, LPCWSTR applicationName = L"Zenity");

게임 내 자원들을 초기화한다.

### void Run()

게임을 실행시킨다. 함수 안에서 while 루프를 돌며 게임이 종료되기 전까지 실행되고 있다.

### void Shutdown()

게임 내 자원을들 해제한다.


## private

---

### InitializeWindow

화면의 크기를 설정한다.

### bool Frame()

매 프레임마다 호출되는 함수다.
내부적으로는 Update와 Draw 함수를 호출한다.

### bool Update()

게임 내 논리적인 연산을 처리하고 갱신한다. 캐릭터의 이동, 물리 충돌 등이 이에 해당하며

GameObject들의 Update 함수를 호출한다.

### void Draw()

화면에 렌더링될 연산들을 처리한다.

# Scene

각 Scene은 GameObject Hierachy를 가진다.

각 Scene마다 다른 GameObject와 Component들을 사용해 전혀 다른 규칙과 공간을 만들어 낼 수있다.

이와 같은 개념을 통해 LoginScene, BattleScene, EndingScene 등 원하는 장면을 나누어서 사용할 수 있다.  

```c
class CGameObject;

class ISceneBase abstract
{
public:
	virtual ~ISceneBase() {};
	virtual void Init() = 0;
	virtual void Clear() = 0;

	virtual void Update() = 0;
	virtual void Draw() = 0;
	
	virtual void AppendChild(shared_ptr<CGameObject> spGameObject) = 0;
	virtual void RemoveChild(shared_ptr<CGameObject> spGameObject) = 0;
	virtual void RemoveChild(const string& name) = 0;
	virtual void RemoveChild(const string tagName) = 0;

};
```

위의 virtual function들을 override 해 다른 Scene을 구현할 수 있다.

```c
class CBeginScene : public CSceneBase
{
private:
	void InitPlayerCharacter();
	void InitBulletSpawner();

public:
	CBeginScene();
	virtual ~CBeginScene();

	void Init() override;
	void Clear() override;
};

static SceneRegistrar<CBeginScene> registrar("BeginScene");
``` 

마지막 줄의 SceneRegistrar 이용해 SceneMgr에 만든 Scene을 등록하고 SceneMgr가 이름으로 호출 할 수 있게 한다.  
```c
static SceneRegistrar<CBeginScene> registrar("BeginScene");
```

SceneRegistrar는 SceneMgr에 Scene을 등록하기 편하게 해주는 유틸성 템플릿 객체로 다음과같이 lambda를 사용하여 구현되어 있다.

```c
template<class T>
class SceneRegistrar {
public:
	SceneRegistrar(const string& sceneName)
	{
		// register the class factory function 
		CSceneMgr::GetInstance()->RegisterScene(sceneName,
			[](void) -> shared_ptr<ISceneBase> 
			{
				return make_shared<T>(); 
			}
		);
	}
};
```


## public
---

### virtual void Init()

Scene에서 필요한 자원들을 초기화한다.

### virtual void Clear()

Scene에서 사용한 자원들을 해제한다.

### virtual void Update()

게임의 논리적인 연산을 처리하고 갱신한다. FirstDepth GameObject의 Update를 호출하며, GameObject들은 본인의 Child Game Object의 Update를 재호출한다. 

### virtual void Draw()
Game Object가 Renderer를 가지고 있다면 Renderer가 Draw 처리를 한다. GameObject들은 본인의 Child Game Object의 Draw를 재호출한다. 

### void AppendChild(shared_ptr<CGameObject> spGameObject)

Scene Hierachy의 First Dept Child Game Object 를 추가한다.

### void RemoveChild(shared_ptr<CGameObject> spGameObject);

Scene Hierachy의 First Dept Child Game Object 를 제거한다.


# SceneMgr 

SceneMgr는 Scene을 등록하고 관리한다. 또한 필요한 Scene을 올리고 내릴 수 있다.

여러개의 Scene을 로드해서 필요한 Scene끼리 조합 할 수 있다.

```c

class CSceneMgr
{
	friend class CGame;

private:
	map<string, shared_ptr<ISceneBase>> m_loadedSceneMap;
	map<string, std::function<shared_ptr<ISceneBase>(void)>> m_sceneFactoryRegistry;

private:
	CSceneMgr();
	~CSceneMgr();

	void UnloadAllScene();

public:
	static CSceneMgr* GetInstance();

	bool Init();
	void Release();
	void LoadScene(const string& name);
	void UnloadScene(const string& name);
	void RegisterScene(const string& sceneName, std::function<shared_ptr<ISceneBase>(void)> generatorFunc);
};

```

## public
---

### bool Init()

SceneMgr를 초기화한다.

### void Release()

SceneMgr의 모든 Scene을 Unload 하고 기타 자원을 모두 해제한다.

### void LoadScene(const string& name)

Scene의 이름을 통해 Scene을 올린다.

### void UnloadScene(const string& name)

Scene의 이름을 통해 Scene을 내린다. 

### void RegisterScene(const string& sceneName, std::function<shared_ptr<ISceneBase>(void)> generatorFunc)

Scene을 등록하며 param에는 Scene의 이름과, Scene을 생성해 반환할 함수를 넣어줘야한다.

# GameObject

게임 오브젝트는 Scene을 구성하는 기본 단위이다.

프로그래머는 GameObject에 다양한 Component들을 붙여서 객체를 만들어 갈 수 있다..

GameObject는 각자 고유한 uuid를 가지며 Child Object를 추가 할 수 있다.

```js
class CGameObject final
{
public:
	CGameObject();
	~CGameObject();

	void AppendChild(shared_ptr<CGameObject> spGameObject);
	void RemoveChild(shared_ptr<CGameObject> spGameObject);

	CGameObject& SetTagName(const std::string& tagName);
	inline const std::string& GetTagName() const { return m_strTagName; };

	CGameObject& SetName(const std::string& tagName);
	inline const std::string& GetName() const { return m_strName; };
	
	void AddComponent(shared_ptr<CComponentBase> spComponent);

	inline void SetActive(bool active) { m_bIsActive = active; }
	inline const bool IsActive() const { return m_bIsActive; }

	template<class T>
	weak_ptr<T> GetComponent()
	{
		for (auto it : m_componentVec)
		{
			weak_ptr<T> spComponent = dynamic_pointer_cast<T>(it);
			if (spComponent.lock() != nullptr)
			{
				return spComponent;
			}
		}
		
		weak_ptr<T> empty;
		return empty;
	};
};
```

## public
---
## void AppendChild(shared_ptr<CGameObject> spGameObject)

해당 GameObject의 Child Game Object 를 추가한다.

## void RemoveChild(shared_ptr<CGameObject> spGameObject);

해당 GameObject의 Child Game Object 를 제거한다.

## void AddComponent(shared_ptr<CComponentBase> spComponent);

해당 GameObject 에 Component를 추가한다.

## weak_ptr<T> GetComponent()

해당 GameObject가 가지고있는 Comopnent를 반한환다.

사용 예는 다음과 같다.

```c
weak_ptr<CTransform> wpTransform = spGameObject->GetComponent<CTransform>();
```

# ComponentBase

Component의 기본 클래스이다. 이 클래스를 상속받아 다양한 컴포넌트들을 만들 수 있다.

```c
class CComponentBase
{
protected:
	CGameObject* m_thisGameObject;

public:
	CComponentBase();
	virtual ~CComponentBase();

	virtual const ComponentFamilyType GetFamilyComponentType() const;
	
	virtual void Init() {};
	virtual void Update() {};
	virtual void Clear() {};

	void SetParent(CGameObject* pGameObject);
};
```

## public
---

## virtual const ComponentFamilyType GetFamilyComponentType() const;

한 오브젝트의 여러개의 Component가 붙으면 안되는 경우가 있다. 예를 들면 CTransform Component가 두개가 붙을수 없다.

기존에 가지고있는 Component들의 ComponentFamilyType과 추가되는 Component의 ComponentFamilyType 비교하여 삽입 할수 있게 되기 때문에

만약 중복되지 않게 처리하고싶다면 이 함수를 override 해야 한다.

## virtual void Init() {};

컴포넌트가 가지고 있는 자원들을 초기화해주는 함수이다.

## virtual void Update() {};

매 프레임 마다 호출되며 Component의 내부 동작을 구현한다.

## virtual void Clear() {};

Component가 지워질 때 호출되는 함수이다.


# Transform 

미리 정의된 Component이다. 오브젝트당 하나만을 가질 수 있으며, Object의 회전, 위치 값을 담당한다.

```c
class CTransform : public CComponentBase
{
private:
	D3DXVECTOR3 m_vPosition;
	D3DXVECTOR3 m_vRotation;

public:
	CTransform();
	virtual ~CTransform();

	const ComponentFamilyType GetFamilyComponentType() const final;
	void Init() override;
	void Update() override;
	void Clear() override;

	inline void Translate(const D3DXVECTOR3& addPos) { m_vPosition += addPos; }
	inline void SetPosition(const D3DXVECTOR3& pos) { m_vPosition = pos; }

	const D3DXVECTOR3& GetPosition() const;
	const D3DXVECTOR3& GetRotation() const;
};
```