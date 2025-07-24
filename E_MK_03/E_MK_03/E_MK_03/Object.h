#pragma once
#include "pch.h"
#include "AnimationClip.h"
#include "Component.h"
#include "InputManager.h"
#include "Transform.h"

using namespace D2DTM;

class Object //발사되는 투사체도 되겠는데
{
public: 
	 Object() = default;
	 virtual ~Object();

	 virtual void Update(){}; //상태 업데이트 일 수도 있고, 그 button level에서 이건 구체화 시켜야 함 
	 virtual void Render(){};
public:
	void SetCurrentClip(const AnimationClip& clip);
	 void AddClip(const std::string& aniName, const AnimationClip& clip);

	 AnimationClip& GetCurrentClip();
	 AnimationClip* GetClip(const std::string& aniName);


	 Transform& GetTransform();
	 void SetPosition(POINT position, SIZE size); //position 값은 update를 통해서 바뀌어야 하겠지 
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
	static_assert(std::is_base_of<Component, T>::value, "Component의 자식이어야 한다는 거임 ");

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
		// fold expression을 통해 첫 번째로 dynamic_cast 성공한 타입을 찾아냄
		ListenerComponent* listener = nullptr;

		// Lambda로 하나씩 검사
		(..., (listener = listener ? listener : dynamic_cast<Types*>(it->get())));

		if (listener)
		{
			InputManager::Get().m_broadcaster->RemoveListener(listener);
		}
	}

	m_Components.clear();

}