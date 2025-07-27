#pragma once
#include "pch.h"
#include "AnimationClip.h"
#include "Component.h"
#include "InputManager.h"
#include "Transform.h"
#include "SpriteRenderer.h"

using namespace D2DTM;

class Object //�߻�Ǵ� ����ü�� �ǰڴµ�
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

	 //Component ������ ä���ߴٸ�, ������ Component��ü�� �������̶� ����� ����.
	 Transform& GetTransform();
	 SpriteRenderer& GetSpriteRenderer();

	
	 void SetPosition(POINT position, SIZE size); //position ���� update�� ���ؼ� �ٲ��� �ϰ��� 
	 void Delete(); //������ ������Ʈ�� ����� �Լ�, �������̱� �ϴٸ�, Ȥ���� �𸣴�!


protected:
	//���� ������Ʈ ������ ���� ���� �����̱� ������, �� ���� �� ���� �ƿ� ���� ����. ����� ����
	template<typename T, typename... Args>
	T* AddComponent(Args&&... args);

	template<typename T>
	T* GetComponent() const;

	void ComponentClear();

protected:

	std::unordered_map<std::string, AnimationClip> m_clips; //�ִϸ��̼� �̸��̶� clip ����
	AnimationClip m_CurrentClip;

	SIZE size;  

	std::vector<std::unique_ptr<Component>> m_Components;
	Transform m_transform;
	SpriteRenderer m_spriterenderer; 

};



//���� ���� ���� ���� Component �Լ� ģ����
#pragma region Component
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
inline T* Object::GetComponent() const //�̰� �� ���Ÿ� Component ������ �� �ʿ䰡 ���� ����?
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
