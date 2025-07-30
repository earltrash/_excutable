#pragma once
#include "pch.h"
#include "UIUtility.h"

class IUIWindow 
{
public:
		virtual ~IUIWindow() = default;
		virtual void Update(float deltaTime) = 0;
		virtual void Render(ID2D1RenderTarget* renderTarget) = 0;
		virtual void HandleInput(const Vec2& mousePos, bool mouseDown, bool mouseUp) = 0;

		virtual void Activate() = 0;
		virtual void Deactivate() = 0;
		virtual bool IsActive() const = 0;

		// â�� ��ġ �� ũ�� (Z-order ó���� ���� �ʿ�)
		virtual Rect GetBounds() const = 0;
		virtual int GetZOrder() const = 0;	// ������ ������.

		// â �̵� (�巡�� ��� ���� ����)
		virtual void SetPosition(const Vec2& newPos) = 0;

		// â �ĺ���. ������
		virtual std::string GetWindowID() const = 0;
private:

};