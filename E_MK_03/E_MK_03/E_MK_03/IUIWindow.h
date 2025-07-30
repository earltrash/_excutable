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

		// 창의 위치 및 크기 (Z-order 처리를 위해 필요)
		virtual Rect GetBounds() const = 0;
		virtual int GetZOrder() const = 0;	// 렌더링 순서임.

		// 창 이동 (드래그 기능 등을 위해)
		virtual void SetPosition(const Vec2& newPos) = 0;

		// 창 식별자. 디버깅용
		virtual std::string GetWindowID() const = 0;
private:

};