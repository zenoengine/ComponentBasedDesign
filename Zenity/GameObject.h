#pragma once
#include "ComponentType.h"

class CComponentBase;

class CGameObject
{
private:
	static unsigned int g_objectuuid;
	unsigned int m_uuid;
	string m_strTagName;
	string m_strName;
	bool m_bIsActive;

	vector<shared_ptr<CGameObject>> m_gameObjectVec;
	vector<shared_ptr<CComponentBase>> m_componentVec;

private:
	void ClearComponentMap();
	void UpdateChild();
	void DrawChild();
	void ClearChild();

public:
	CGameObject();
	virtual ~CGameObject();

	virtual void Init();
	virtual void Update();
	virtual void Clear();

	void Draw();

	void AppendChild(shared_ptr<CGameObject> spGameObject);
	void RemoveChild(shared_ptr<CGameObject> spGameObject);

	CGameObject& SetTagName(const std::string& tagName);
	inline const std::string& GetTagName() const { return m_strTagName; };

	CGameObject& SetName(const std::string& tagName);
	inline const std::string& GetName() const { return m_strName; };
	
	void AddComponent(shared_ptr<CComponentBase> spComponent);
	void UpdateComponent();

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