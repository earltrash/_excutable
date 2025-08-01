#pragma once
#include "pch.h"
#include "AnimationClip.h"
#include "Component.h"
#include "InputManager.h"
#include "Transform.h"
#include "SpriteRenderer.h"

using namespace D2DTM;

class Object //발사되는 투사체도 되겠는데
{
public: 
	 Object() = default;
	 virtual ~Object();

	 virtual void Update(){}; 
	 virtual void Render(){};
public:
	 void SetCurrentClip(const AnimationClip& clip);
	 void AddClip(const std::string& aniName, const AnimationClip& clip);

	 AnimationClip& GetCurrentClip();
	 AnimationClip* GetClip(const std::string& aniName);

	 //Component 구조를 채택했다만, 아직은 Component자체가 고정적이라 멤버로 접근.
	 Transform& GetTransform();
	 SpriteRenderer& GetSpriteRenderer();

	
	 void SetPosition(POINT position); //position 값은 update를 통해서 바뀌어야 하겠지 
	 void Delete(); //소유한 컴포넌트를 지우는 함수, 고정적이긴 하다만, 혹여나 모르니!


protected:
	//차피 컴포넌트 변동이 거의 없는 게임이기 때문에, 이 둘은 쓸 일이 아예 없을 듯함. 멤버로 접근
	template<typename T, typename... Args>
	T* AddComponent(Args&&... args);

	template<typename T>
	T* GetComponent() const;

	void ComponentClear();

protected:


	list<Object> m_list; 
	std::unordered_map<std::string, AnimationClip> m_clips; //애니메이션 이름이랑 clip 정보
	AnimationClip m_CurrentClip;
	SIZE size;  
	std::vector<std::unique_ptr<Component>> m_Components;

	Transform m_transform;
	SpriteRenderer m_spriterenderer; 
	bool activated = false;
};



//거의 볼일 없을 듯한 Component 함수 친구들
#pragma region Component
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
inline T* Object::GetComponent() const //이걸 안 쓸거면 Component 구조를 쓸 필요가 없긴 하지?
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
#pragma endregion
