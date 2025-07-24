#pragma once
#include "pch.h"
#include "Listener.h"

using Callback = std::function<void(const MSG&)>;

class MouseListenerComponent : public ListenerComponent //새로운 shared-raw-shared로 소유권 이중화를 막기 위함.
{
public:
	explicit MouseListenerComponent(Callback cb) : callback(std::move(cb)) {}
	~MouseListenerComponent() = default;

	void _OnEvent(const MSG& msg) override {

		if (callback) callback(msg);
	};
	bool Matches(const MSG& msg)const {
		return msg.message >= WM_MOUSEFIRST && msg.message <= WM_MOUSELAST;

	};  // 관심 있는 메시지만 받게
private:
	Callback callback;
};
