#pragma once
#include "pch.h"
#include "AnimationClip.h"
#include "Component.h"
#include "InputManager.h"
#include "Transform.h"

using namespace D2DTM;

class Object //�߻�Ǵ� ����ü�� �ǰڴµ�
{
public: 
	 Object() = default;
	 virtual ~Object();

	 virtual void Update(){}; //���� ������Ʈ �� ���� �ְ�, �� button level���� �̰� ��üȭ ���Ѿ� �� 
	 virtual void Render(){};
public:
	void SetCurrentClip(const AnimationClip& clip);
	 void AddClip(const std::string& aniName, const AnimationClip& clip);

	 AnimationClip& GetCurrentClip();
	 AnimationClip* GetClip(const std::string& aniName);


	 Transform& GetTransform();
	 void SetPosition(POINT position, SIZE size); //position ���� update�� ���ؼ� �ٲ��� �ϰ��� 
	 void Delete();

protected:
	template<typename T, typename... Args>
	T* AddComponent(Args&&... args);

	template<typename T>
	T* GetComponent() const;

	template<typename... Types>
	void ComponentClear();

protected:

	std::unordered_map<std::string, AnimationClip> m_clips; 
	AnimationClip m_CurrentClip;

	SIZE size;    


	std::vector<std::unique_ptr<Component>> m_Components;
	Transform m_transform;
};

template<typename T, typename ...Args>
inline T* Object::AddComponent(Args && ...args)
{
	static_assert(std::is_base_of<Component, T>::value, "Component�� �ڽ��̾�� �Ѵٴ� ���� ");

	auto comp = std::make_unique<T>(std::forward<Args>(args)...);

	comp->SetOwner(this);

	T* ptr = comp.get();

	m_Components.emplace_back(std::move(comp));

	return ptr;
}

template<typename T>
inline T* Object::GetComponent() const
{
	for (auto& com : m_Components)
	{
		if (auto ptr = dynamic_cast<T*>(com.get()))
		{
			return ptr;
		}
	}

	return nullptr;
}

template<typename... Types>
inline void Object::ComponentClear() {
	for (auto it = m_Components.begin(); it != m_Components.end(); ++it)
	{
		// fold expression�� ���� ù ��°�� dynamic_cast ������ Ÿ���� ã�Ƴ�
		ListenerComponent* listener = nullptr;

		// Lambda�� �ϳ��� �˻�
		(..., (listener = listener ? listener : dynamic_cast<Types*>(it->get())));

		if (listener)
		{
			InputManager::Get().m_broadcaster->RemoveListener(listener);
		}
	}

	m_Components.clear();

}